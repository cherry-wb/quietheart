/*TODO
*define SIM_AVP17 0
*/
#include <linux/kernel.h>



#define sfmem_printk(level, format, arg...) \
	printk(level "[SFMEM] %s() @%d :> " format, \
		__FUNCTION__, __LINE__, ## arg)

#define CONFIG_SFMEM_DEBUG 
#ifdef  CONFIG_SFMEM_DEBUG

#define sfmem_debugl(format, arg...) \
	sfmem_printk(KERN_DEBUG, format "\n" , ## arg)/*KERN_DEBUG*/

#define sfmem_infol(format, arg...) \
	sfmem_printk(KERN_NOTICE, format "\n" , ## arg)/*KERN_INFO*/

#define sfmem_warningl(format, arg...) \
	sfmem_printk(KERN_WARNING, format "\n" , ## arg)

#define sfmem_errorl(format, arg...) \
	sfmem_printk(KERN_ERR, "Error! " format "\n" , ## arg)

#else /* CONFIG_SFMEM_DEBUG */

#define sfmem_debugl(format, arg...)

#define sfmem_infol(format, arg...)

#define sfmem_warningl(format, arg...)

#define sfmem_errorl(format, arg...) \
	sfmem_printk(KERN_ERR, "Error! " format "\n" , ## arg)

#endif /* CONFIG_SFMEM_DEBUG */


//==============================================================================
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/delay.h>

#include <asm/io.h>
#include <asm/uaccess.h>

#include <mach/hardware.h>
#include <mach/gpio.h>



/*lvkai+[*/
/*XXX simluate the avp17 on avp13*/
#define SIM_AVP17 0
/*lvkai+]*/

#define SFMEM_TOTALSIZE                 (0x100000*16) /* 16MB memory */

/*lvkai+[*/
#if SIM_AVP17 == 1
#undef SFMEM_TOTALSIZE
#define SFMEM_TOTALSIZE                 (0x100000*8) /* 8MB memory */
#endif
/*lvkai+]*/

#define SFMEM_ERASESIZE                 0x1000 /* 4KB */
#define SFMEM_ERASEBLKS                 0x1000 /* 4KB */
#if defined(CONFIG_AVP17_SUPPORT) && defined(CONFIG_DUAL_FLASH)
#define SFMEM_CHIP_NUM                  2
#else
#define SFMEM_CHIP_NUM                  1
#endif

/*lvkai+[*/
#if SIM_AVP17 == 1
#undef SFMEM_CHIP_NUM
#define SFMEM_CHIP_NUM                  2
/*use the ram to simlute the flash1*/
char mem_chip1[SFMEM_TOTALSIZE];
#endif

/*add the avp17 dual flash to one support*/
#define SFMEM_DUAL 1
#define SFDUALMEM_TOTALSIZE					(SFMEM_TOTALSIZE * SFMEM_CHIP_NUM) /* 16xSFMEM_CHIP_NUM MB */
/*lvkai+]*/

enum {
	SFMEM_IOCTL_PROGRAM,
	SFMEM_IOCTL_ERASE,
	SFMEM_IOCTL_ERASE_SAFE,
};
struct sfmem_op {
	unsigned int off;
	unsigned int len;
	unsigned int buf;
};

//------------------------------------------------------------------------------
// nor flash related definitions

/* timeout (in usec) */
#define NOR_TIMEOUT_PROGRAM_US          (2 * 1000)      /* 2 ms */
#define NOR_TIMEOUT_PROGRAM_STEP_US     (1)             /* check every 1 usec */

/* timeout (in msec) */
#define NOR_TIMEOUT_ERASE_MS            (30 * 1000)     /* 30 sec */
#define NOR_TIMEOUT_ERASE_STEP_MS       (1)             /* check every 1 msec */

#define ERR_NOR_INVALID_DEVICE          -1
#define ERR_NOR_DATA_NOT_ALIGNED        -2
#define ERR_NOR_WRITE_FAILED            -3
#define ERR_NOR_VERIFY_FAILED           -4
#define ERR_NOR_TIMEOUT                 -5
#define ERR_NOR_BAD_ADDRESS             -6

/* Winbond IDs */
#define VENDOR_WINBOND                  0x00ef
#define W25X64                          0x3017
#define W25Q128                         0x4018

/* memory info */
#define SFMEM_MEM_PHYS_BASE             0xFF000000
#define SFMEM_PAGE_SIZE			0x100 /* 256 Bytes */

/* control register info */
#define SFMEM_REG_PHYS_BASE             0xE0020000
#define SFMEM_REG_SIZE                  (0x400) /* 1KB registers */

/* control register address */
#define REG_SFMCOM                      0x10
#define REG_SFMCMD                      0x14
#define SFMCMD_ROM_ACCESS               0x0000
#define SFMCMD_DIRECT_CON               0x0001

/* control commands */
#define FLASH_CMD_WRITE_ENABLE          0x06
#define FLASH_CMD_READID                0x9f
#define FLASH_CMD_READ_STATUS           0x05
#define FLASH_STATUS_WIP                0x01
#define FLASH_CMD_PAGE_PROGRAM          0x02
#define FLASH_CMD_SUBSECTOR_ERASE       0x20
#define FLASH_CMD_SECTOR_ERASE          0xd8


//------------------------------------------------------------------------------
// nor flash related structions

struct nor_flash {
	u16 vendor_id;
	u16 device_id;
	u32 size;               //total bytes
	u32 block_size;         //block size
	u32 numblocks;          //blocks number
	u32 eraseblk_size;      //erase block size
	u32 numeraseblks;       //erase blocks number
	u8 * phys_regs;         //ctrl register physical address
	u8 * regs;              //ctrl register virtual address
	u8 * phys_base;         //memory physical address
	u8 * base;              //memory virtual address
#if SIM_AVP17 == 1
	u8 * unuse0;
#endif
};

static struct nor_flash sfmem_stat = {
	.vendor_id      = VENDOR_WINBOND,
/*lvkai*[*/
#if SIM_AVP17 == 1
	.device_id		=W25X64,
#else
	.device_id      = W25Q128,
#endif
/*lvkai*]*/
	.size			= SFDUALMEM_TOTALSIZE, /*lvkai+*/
	.block_size     = SFMEM_ERASESIZE,
	.numblocks      = SFMEM_ERASEBLKS,
	/* what is the difference between block and erase-block ? */
	.eraseblk_size  = SFMEM_ERASESIZE,
	.numeraseblks   = SFMEM_ERASEBLKS,
	.phys_regs      = (void*)SFMEM_REG_PHYS_BASE,
	.regs           = NULL,
	.phys_base      = (void*)SFMEM_MEM_PHYS_BASE,
	.base           = NULL,
#if SIM_AVP17 == 1
	.unuse0			= NULL,
#endif

};


//------------------------------------------------------------------------------
// functions

/* control register helper */
inline void SPI_BEGIN(void) {
	writel(SFMCMD_DIRECT_CON, sfmem_stat.regs + REG_SFMCMD);
}
inline void SPI_END(void) {
	writel(SFMCMD_ROM_ACCESS, sfmem_stat.regs + REG_SFMCMD);
}
inline u32 SPI_READ(void) {
	return readl(sfmem_stat.regs + REG_SFMCOM);
}
inline void SPI_WRITE(u32 val) {
	writel((val), sfmem_stat.regs + REG_SFMCOM);
}

#ifdef CONFIG_AVP17_SUPPORT
static int sfmem_cs = -1;
static inline void sfmem_chip_select(int ch) {
	if (sfmem_cs == ch) {return;}
	switch(ch) {
	case 0:
		diablo_set_gpio_dataout(DIABLO_BGPIO_05, 0);
		diablo_set_gpio_dataout(DIABLO_BGPIO_21, 1);
		break;
	case 1:
		diablo_set_gpio_dataout(DIABLO_BGPIO_05, 1);
		diablo_set_gpio_dataout(DIABLO_BGPIO_21, 0);
		break;
	default:break;
	}
	sfmem_cs = ch;
}
#else
#if SIM_AVP17 == 1
static inline void sfmem_chip_select(int ch) {
	switch(ch) {
	case 0:
	if(NULL != sfmem_stat.unuse0 && sfmem_stat.unuse0 != mem_chip1)
	{
		sfmem_stat.base = sfmem_stat.unuse0;
	}
	sfmem_stat.unuse0 = mem_chip1;
	
	break;
	case 1:
	if(NULL != sfmem_stat.base && sfmem_stat.base != mem_chip1)
	{
		sfmem_stat.unuse0 = sfmem_stat.base;
	}
	sfmem_stat.base = mem_chip1;
	break;
	}
}
#else
#define sfmem_chip_select(ch) ((void)ch)
#endif
#endif

/* get the vendor id and device id */
static void sfmemc_nor_read_id(uint16_t *vendor_id, uint16_t *device_id)
{
	/* sanity check */
	if (vendor_id == NULL) {
		sfmem_errorl("vendor_id is NULL");
		return;
	}
	if (device_id == NULL) {
		sfmem_errorl("device_id is NULL");
		return;
	}

	/* Read ID */
	SPI_BEGIN();
	SPI_WRITE(FLASH_CMD_READID);
	*vendor_id  = SPI_READ();
	*device_id  = SPI_READ() << 8;
	*device_id |= SPI_READ() << 0;
	SPI_END();
}

/* internal function */
static int check_status(int timeout, int step, int program)
{
	int ret = 0;

	SPI_BEGIN();
	SPI_WRITE(FLASH_CMD_READ_STATUS);

	while (SPI_READ() & FLASH_STATUS_WIP) {
		timeout -= step;
		if (timeout <= 0) {
			/* Timeout */
			ret = ERR_NOR_TIMEOUT;
			break;
		}
		/* program */
		if (program) { udelay(step); }
		/* erase */
		else { mdelay(step); }
	}

	SPI_END();

	return ret;
}

/* internal function */
int sfmemc_nor_erase_block(u32 offset)
{
	int ret;
	u8 cmd;

	/* Write Enable */
	SPI_BEGIN();
	SPI_WRITE(FLASH_CMD_WRITE_ENABLE);
	SPI_END();

	/* Block Erase */
	cmd = FLASH_CMD_SUBSECTOR_ERASE;

	SPI_BEGIN();
	SPI_WRITE(cmd);
	SPI_WRITE((offset >> 16) & 0xff);
	SPI_WRITE((offset >>  8) & 0xff);
	SPI_WRITE((offset >>  0) & 0xff);
	SPI_END();

	/* wait for erase completion */
	ret = check_status(NOR_TIMEOUT_ERASE_MS, NOR_TIMEOUT_ERASE_STEP_MS, 0);

	return ret;
}

/* internal function */
int sfmemc_nor_program_buf(u32 off, const char *data, int len)
{
	int i;
	int ret;
	unsigned int program_len;

	if (data == NULL) {
		sfmem_errorl("data is NULL");
		return ERR_NOR_BAD_ADDRESS;
	}

	while (len > 0) {
		/* calculate data length to program */
		if (len > SFMEM_PAGE_SIZE)
			program_len = SFMEM_PAGE_SIZE;
		else
			program_len = len;

		/* Write Enable */
		SPI_BEGIN();
		SPI_WRITE(FLASH_CMD_WRITE_ENABLE);
		SPI_END();

		/* Page Program */
		SPI_BEGIN();
		SPI_WRITE(FLASH_CMD_PAGE_PROGRAM);
		SPI_WRITE((off >> 16) & 0xff);
		SPI_WRITE((off >>  8) & 0xff);
		SPI_WRITE((off >>  0) & 0xff);
		for (i = 0; i < program_len; i++) {
			SPI_WRITE(*data++);
		}
		SPI_END();

		/* wait for program completion */
		ret = check_status(NOR_TIMEOUT_PROGRAM_US * program_len,
				NOR_TIMEOUT_PROGRAM_STEP_US, 1);
		if (ret < 0)
			return ret;

		off += program_len;
		len -= program_len;
	}

	return 0;
}

/* 
 * Erase specifed address on device.
 *
 * Requires:
 *    - address to erase
 *    - length to erase (in bytes)
 *
 * Returns:
 *    - On success, 0.
 *    - On failure, returns error number (<0)
 *      and pointer to block failed to erase.
 *
 * Rationale:

|  block n   |  block n+1 |
|--------####|##----------|

-: original data
#: region to erase

the given offset is the position of the '#' region, but after this 
function returns, both block_n and block_n+1 will be ereased. And 
the original data in the two block will be lost, even if it is not 
in the requested region.
NOTE: sfmem driver has no duty to keep those orignal data, the caller
    should do this if necessary.

 */
int sfmem_erase(u32 offset, int len)
{
	u32 workpos;
	int worklen;
	int erased_blks;
	int i;
	int retval = 0;

	/* assert params */

	erased_blks = 0;

	/* round the address at block address */
	workpos = offset & ~(sfmem_stat.eraseblk_size - 1);

	/* workpos might be smaller than offset, so worklen should be greater */
	worklen = len + (offset - workpos);

	do {
		/* call relocated code */
		if ((retval = sfmemc_nor_erase_block(workpos)) < 0) {
			sfmem_errorl("erase block failed");
			return retval;
		}

		erased_blks++;
		worklen -= sfmem_stat.eraseblk_size;
		workpos += sfmem_stat.eraseblk_size;
	} while (worklen > 0);

	/* erase done */

	/* verify */
	for (i=0; i<len; i++) {
		if ( *(sfmem_stat.base+offset+i) != 0xff) {
			sfmem_errorl("0x%08x + 0x%x = 0x%02x", 
					(u32)offset, i, 
					*(sfmem_stat.base+offset + i));
			sfmem_errorl("Verify failed !!");
			retval = ERR_NOR_VERIFY_FAILED;
			break;
		}
	}

	return retval;
}

/* 
 * Programs flash
 *
 * Requires:
 *   - offset to program.
 *   - data to program
 *   - length in bytes to program
 * Returns:
 *   - On success, returns 0.
 *   - On failure, return error number.
 * NOTE:
 *   - Nor flash must be erased before program.
 */
int sfmem_program(u32 offset, const char *data, int len)
{
	int retval = 0;
	int size;

	while (len > 0) {
		size = (len < sfmem_stat.eraseblk_size) 
			? len : sfmem_stat.eraseblk_size;

		/* call relocated code */
		retval = sfmemc_nor_program_buf(offset, data, size);

		len -= size;
		offset += size;
		data += size;
	}

	return retval;
}    

//==============================================================================

static int sfmem_chardev_open(struct inode * node, struct file * f)
{
	int minor = MINOR(node->i_cdev->dev);

	if (!sfmem_stat.base || !sfmem_stat.regs) { return -ENXIO; }

	sfmem_chip_select(minor);

	return 0;
}

static int sfmem_chardev_release(struct inode * node, struct file * f)
{
	if (!sfmem_stat.base || !sfmem_stat.regs) { return -ENXIO; }

	sfmem_debugl("");
	return 0;
}

static ssize_t sfmem_chardev_read(struct file *f, char __user *buf, 
						size_t nbytes, loff_t *pos)
{
	sfmem_debugl("*pos = 0x%llx, nbytes = 0x%x", *pos, nbytes);
	if (!sfmem_stat.base || !sfmem_stat.regs) { return -ENXIO; }

	if (*pos > SFDUALMEM_TOTALSIZE) {
		return -EINVAL;
	}
	if (*pos == SFDUALMEM_TOTALSIZE) {
		/* pos reach the end, nothing to read. */
		sfmem_chip_select(1);
		return 0;
	}
	nbytes = (*pos + nbytes > SFDUALMEM_TOTALSIZE) 
		? (SFDUALMEM_TOTALSIZE - *pos) 
		: nbytes;
	if(*pos + nbytes < SFMEM_TOTALSIZE || SFMEM_CHIP_NUM == 1)
	{
		sfmem_chip_select(0);
		if (0 != copy_to_user(buf, sfmem_stat.base+*pos, nbytes))
		{
			sfmem_errorl("copy_to_user() failed !!");
			return -EFAULT;
		}
		//*pos += nbytes;
	}
	else
	{//XXX
		if(*pos < SFMEM_TOTALSIZE)
		{
			udelay(100);//XXX
			sfmem_chip_select(0);
			udelay(100);//XXX
			if (0 != copy_to_user(buf, sfmem_stat.base+*pos, (SFMEM_TOTALSIZE - *pos)))
			{
				sfmem_errorl("copy_to_user() failed !!");
				return -EFAULT;
			}
			udelay(100);//XXX
			sfmem_chip_select(1);
			udelay(100);//XXX
			if (0 != copy_to_user(buf+SFMEM_TOTALSIZE-*pos, 
				sfmem_stat.base, (nbytes - (SFMEM_TOTALSIZE - *pos))))
			{
				sfmem_errorl("copy_to_user() failed !!");
				return -EFAULT;
			}
			//*pos += nbytes;
		}
		else
		{
			sfmem_chip_select(1);
			if (0 != copy_to_user(buf, sfmem_stat.base+*pos-SFMEM_TOTALSIZE, nbytes))
			{
				sfmem_errorl("copy_to_user() failed !!");
				return -EFAULT;
			}
			//*pos += nbytes;
		}
	}
	*pos += nbytes;
	return nbytes;
}

/*
* Write means erase first and then program immediately.
* So, if the caller wants to program flash frequently, it had better use
* ioctl() to erase a big region first, and then do program each time, instead
* of write each time.
* NOTE: write() is safe, nothing will be lost in write() function.
*       but it is slow. if the start address and data length are not aligned 
*       against erase-block, the write() will erase and copy some extra data 
*       to force the alignment. so if you have to write the flash frequently 
*       with small size data for each time, you'd better use ioctl() to erase
*       once and program many times.
*/
static char tempbuf[SFMEM_ERASESIZE];
static ssize_t sfmem_chardev_write(struct file * f, const char __user * buf, 
						size_t nbytes, loff_t * pos)
{
	const size_t e_size = sfmem_stat.eraseblk_size;
	int left = nbytes;

	sfmem_debugl("*pos = 0x%llx, nbytes = 0x%x", *pos, nbytes);
	
	/* need to assert params, to make sure *pos and nbytes are available */
	if (!sfmem_stat.base || !sfmem_stat.regs) { return -ENXIO; }
	if (*pos > sfmem_stat.size || *pos+nbytes > sfmem_stat.size) {
		sfmem_errorl("*pos=0x%llx, nbytes=0x%x, totalsize=0x%x", 
				*pos, nbytes, sfmem_stat.size); /**pos, nbytes, e_size);*/
		return -EINVAL;
	}
	if (*pos == sfmem_stat.size) {
		/* already reach the end, no room to write. */
		sfmem_chip_select(1);
		return 0;
	}
/*XXX*/
	if(*pos + nbytes < SFMEM_TOTALSIZE || SFMEM_CHIP_NUM == 1)
	{
		sfmem_chip_select(0);
		do
		{

			int off = *pos;
			int count = min_t(int, left, e_size);
			int workpos = off;

			if (off & (e_size-1))
			{
				/* write head partial erase-block, need keep orig data */
				workpos = off & ~(e_size - 1);
				count = min_t(int, left, (e_size-(off-workpos)));

				memcpy(tempbuf, sfmem_stat.base+workpos, e_size);
				if(copy_from_user(tempbuf+(off-workpos), buf, count))
				{
					return -EFAULT;
				}
				sfmem_erase(workpos, e_size);
				sfmem_program(workpos, tempbuf, e_size);
			}
			else
			{
				if (count == e_size)
				{
					/* write entire erase-block */
					if(copy_from_user(tempbuf, buf, e_size))
					{
						return -EFAULT;
					}
					sfmem_erase(workpos, e_size);
					sfmem_program(workpos, tempbuf, e_size);
				}
				else
				{
					/* write tail partial erase-block, need keep orig data */
					memcpy(tempbuf, sfmem_stat.base+workpos, e_size);
					if(copy_from_user(tempbuf, buf, count))
					{
						return -EFAULT;
					}
					sfmem_erase(workpos, e_size);
					sfmem_program(workpos, tempbuf, e_size);
				}
			}

			left -= count;

			sfmem_debugl("workpos=0x%x, buf=0x%p, count=0x%x, left=0x%x", 
					workpos, buf, count, left);

			buf += count;
			*pos = off + count;

		} while(left > 0);
	}
	else
	{//XXX
		if(*pos < SFMEM_TOTALSIZE)
		{
			int left0 = SFMEM_TOTALSIZE - *pos;
			int left1 = left - left0;
			udelay(100);//XXX
			sfmem_chip_select(0);
			udelay(100);//XXX
			do
			{

				int off = *pos;
				int count = min_t(int, left0, e_size);
				int workpos = off;

				if (off & (e_size-1))
				{
					/* write head partial erase-block, need keep orig data */
					workpos = off & ~(e_size - 1);
					count = min_t(int, left0, (e_size-(off-workpos)));

					memcpy(tempbuf, sfmem_stat.base+workpos, e_size);
					if(copy_from_user(tempbuf+(off-workpos), buf, count))
					{
						return -EFAULT;
					}
					sfmem_erase(workpos, e_size);
					sfmem_program(workpos, tempbuf, e_size);
				}
				else
				{
					if (count == e_size)
					{
						/* write entire erase-block */
						if(copy_from_user(tempbuf, buf, e_size))
						{
							return -EFAULT;
						}
						sfmem_erase(workpos, e_size);
						sfmem_program(workpos, tempbuf, e_size);
					}
					else
					{
						/* write tail partial erase-block, need keep orig data */
						memcpy(tempbuf, sfmem_stat.base+workpos, e_size);
						if(copy_from_user(tempbuf, buf, count))
						{
							return -EFAULT;
						}
						sfmem_erase(workpos, e_size);
						sfmem_program(workpos, tempbuf, e_size);
					}
				}

				left0 -= count;
				left -= count;

				sfmem_debugl("workpos=0x%x, buf=0x%p, count=0x%x, left0=0x%x", 
						workpos, buf, count, left0);

				buf += count;
				*pos = off + count;

			} while(left0 > 0);

			udelay(100);//XXX
			sfmem_chip_select(1);
			udelay(100);//XXX

			if(SFMEM_TOTALSIZE != *pos )
			{
				sfmem_errorl("write position before flash1 error.*pos=0x%llx", *pos);
				return -EINVAL;
			}
#if SIM_AVP17 == 1
			do
			{
				int off = *pos;
				if(copy_from_user(sfmem_stat.base + off - SFMEM_TOTALSIZE ,buf,left1))
				{
					return -EFAULT;
				}
				buf+=left1;
				*pos= off + left1;
				left -= left1;
			}while(0);
#else
			do
			{

				int off = *pos;
				int count = min_t(int, left1, e_size);
				int workpos = off;

				if ((off-SFMEM_TOTALSIZE) & (e_size-1))
				{/*XXX never reach here!*/
					/* write head partial erase-block, need keep orig data */
					sfmem_errorl("write position on flash1 start position not 0.*pos=0x%llx", *pos);
					workpos = off & ~(e_size - 1);
					count = min_t(int, left1, (e_size-(off-workpos)));

					memcpy(tempbuf, sfmem_stat.base+workpos-SFMEM_TOTALSIZE, e_size);
					if(copy_from_user(tempbuf+(off-workpos), buf, count))
					{
						return -EFAULT;
					}
					sfmem_erase(workpos-SFMEM_TOTALSIZE, e_size);//XXX
					sfmem_program(workpos-SFMEM_TOTALSIZE, tempbuf, e_size);//XXX
				}
				else
				{
					if (count == e_size)
					{
						/* write entire erase-block */
						if(copy_from_user(tempbuf, buf, e_size))
						{
							return -EFAULT;
						}
						sfmem_erase(workpos-SFMEM_TOTALSIZE, e_size);//XXX
						sfmem_program(workpos-SFMEM_TOTALSIZE, tempbuf, e_size);//XXX
					}
					else
					{
						/* write tail partial erase-block, need keep orig data */
						memcpy(tempbuf, sfmem_stat.base+workpos-SFMEM_TOTALSIZE, e_size);
						if(copy_from_user(tempbuf, buf, count))
						{
							return -EFAULT;
						}
						sfmem_erase(workpos-SFMEM_TOTALSIZE, e_size);//XXX
						sfmem_program(workpos-SFMEM_TOTALSIZE, tempbuf, e_size);//XXX
					}
				}

				left1 -= count;
				left -= count;

				sfmem_debugl("workpos=0x%x, buf=0x%p, count=0x%x, left1=0x%x", 
						workpos, buf, count, left1);

				buf += count;
				*pos = off + count;

			} while(left1 > 0);
#endif
			//left = left - left0 -left1;
		}
		else
		{
			sfmem_chip_select(1);
#if SIM_AVP17 == 1
			do
			{
				int off = *pos;
				if(copy_from_user(sfmem_stat.base + off - SFMEM_TOTALSIZE ,buf,left))
				{
					return -EFAULT;
				}
				buf+=left;
				*pos= off + left;
			}while(0);
#else
			do
			{

				int off = *pos;
				int count = min_t(int, left, e_size);
				int workpos = off;

				if ((off-SFMEM_TOTALSIZE) & (e_size-1))
				{
					/* write head partial erase-block, need keep orig data */
					workpos = off & ~(e_size - 1);
					count = min_t(int, left, (e_size-(off-workpos)));

					memcpy(tempbuf, sfmem_stat.base+workpos-SFMEM_TOTALSIZE, e_size);
					if(copy_from_user(tempbuf+(off-workpos), buf, count))
					{
						return -EFAULT;
					}
					sfmem_erase(workpos-SFMEM_TOTALSIZE, e_size);//XXX
					sfmem_program(workpos-SFMEM_TOTALSIZE, tempbuf, e_size);//XXX
				}
				else
				{
					if (count == e_size)
					{
						/* write entire erase-block */
						if(copy_from_user(tempbuf, buf, e_size))
						{
							return -EFAULT;
						}
						sfmem_erase(workpos-SFMEM_TOTALSIZE, e_size);//XXX
						sfmem_program(workpos-SFMEM_TOTALSIZE, tempbuf, e_size);//XXX
					}
					else
					{
						/* write tail partial erase-block, need keep orig data */
						memcpy(tempbuf, sfmem_stat.base+workpos-SFMEM_TOTALSIZE, e_size);
						if(copy_from_user(tempbuf, buf, count))
						{
							return -EFAULT;
						}
						sfmem_erase(workpos-SFMEM_TOTALSIZE, e_size);//XXX
						sfmem_program(workpos-SFMEM_TOTALSIZE, tempbuf, e_size);//XXX
					}
				}

				left -= count;

				sfmem_debugl("workpos=0x%x, buf=0x%p, count=0x%x, left1=0x%x", 
						workpos, buf, count, left);

				buf += count;
				*pos = off + count;

			} while(left > 0);
#endif
		}
	}

	sfmem_debugl("left bytes = 0x%x", left);
	return nbytes;
}

#if SFMEM_DUAL == 1
static int sfmem_chardev_ioctl(struct inode * node, struct file * f, 
					unsigned int cmd, unsigned long arg)
{
	int ret = -1;
	return ret;
}
#else
static int sfmem_chardev_ioctl(struct inode * node, struct file * f, 
					unsigned int cmd, unsigned long arg)
{
	int ret = -1;
	void * __user puser = (void*)arg;
	struct sfmem_op op;

	if (!sfmem_stat.base || !sfmem_stat.regs) { return -ENXIO; }

	sfmem_debugl("cmd=%u, arg=0x%08lx", cmd, arg);

	switch (cmd) {
	case SFMEM_IOCTL_ERASE:
		/* return 0 means success */

		if (copy_from_user(&op, puser, sizeof(op))) { return -EFAULT; }
		ret = sfmem_erase(op.off, op.len); /* buf is not used */
		break;

	case SFMEM_IOCTL_ERASE_SAFE:
		/* return 0 means success */
		/* safe means if the offset and length is not aligned, this 
		command only reports an error and does nothing. */

		if (copy_from_user(&op, puser, sizeof(op))) { return -EFAULT; }
		if (op.off & (sfmem_stat.eraseblk_size-1) 
			|| op.len & (sfmem_stat.eraseblk_size-1))
		{
			sfmem_debugl("off=0x%08x, len=0x%08x", op.off, op.len);
			sfmem_errorl("offset and length must be aligned "
				"against 0x%x", sfmem_stat.eraseblk_size);
			return -EINVAL;
		}
		ret = sfmem_erase(op.off, op.len); /* buf is not used */
		break;

	case SFMEM_IOCTL_PROGRAM:
		/* return 0 means success */

		if (copy_from_user(&op, puser, sizeof(op))) { return -EFAULT; }
		if (op.buf == 0) { return -EINVAL; }
		
		ret = sfmem_program(op.off, (void*)op.buf, op.len);
		break;

	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}
#endif


//------------------------------------------------------------------------------
// char device related definitions and structions

//#define DIABLO_MAJOR_ID_SFMEM           251
#define SFMEM_DRIVER_NAME               "sfmem"

static int sfmem_major = DIABLO_MAJOR_ID_SFMEM;
static struct cdev sfmem_cdev[SFMEM_CHIP_NUM];
static struct file_operations sfmem_fops ={
	.owner   = THIS_MODULE,
	.open    = sfmem_chardev_open,
	.release = sfmem_chardev_release,
	.llseek  = generic_file_llseek,
	.read    = sfmem_chardev_read,
	.write	 = sfmem_chardev_write,
	.ioctl	 = sfmem_chardev_ioctl,
};

int sfmem_cdev_register(int minor_count)
{
	int ret = -1;
	dev_t dev_id = 0;
	struct cdev *p = NULL;

	/* register and init char device */
	dev_id = MKDEV(sfmem_major, 0);
	ret = register_chrdev_region(dev_id, minor_count, SFMEM_DRIVER_NAME);
	if (ret) {
		sfmem_errorl("register_chrdev_region() failed !! minor=%d", minor_count);
		return ret;
	}

	int i;
	for (i=0; i<minor_count; i++)
	{
		p = &sfmem_cdev[i];
		cdev_init(p, &sfmem_fops);
		ret = cdev_add(p, dev_id, 1); //one device support only one minor.
		if (ret)
		{
			sfmem_errorl("cdev_add() failed !! minor=%d", minor_count);
			return ret;
		}
	}

	return 0;
}

void sfmem_cdev_unregister(int minor_count)
{
	dev_t dev_id;

	dev_id = MKDEV(sfmem_major, 0);	
	unregister_chrdev_region(dev_id, 1);
	int i;
	for (i=0; i<minor_count; i++)
	{
		cdev_del(&sfmem_cdev[i]);
	}
}

static int __init sfmem_init(void)
{
	u16 vendor_id = 0;
	u16 device_id = 0;
	
	sfmem_infol("sfmem module start !!");

/*Check information of two flash, and select the first as default start*/
	sfmem_chip_select(0);
	sfmem_stat.size = sfmem_stat.numeraseblks* sfmem_stat.eraseblk_size * SFMEM_CHIP_NUM;
	sfmem_stat.base = ioremap((u32)sfmem_stat.phys_base, sfmem_stat.size / SFMEM_CHIP_NUM);
	sfmem_stat.regs = ioremap((u32)sfmem_stat.phys_regs, SFMEM_REG_SIZE);

	sfmemc_nor_read_id(&vendor_id, &device_id);
	
	if (vendor_id == sfmem_stat.vendor_id 
			&& device_id == sfmem_stat.device_id) {
		sfmem_infol("Flash 1 Vendor[WINBOND], Device[W25Q128],chip num:%d",SFMEM_CHIP_NUM);
	} else {
		sfmem_warningl("Flash 1 Vendor[0x%04x], Device[0x%04x]", 
				vendor_id, device_id);
		return 0;
	}
#ifdef CONFIG_AVP17_SUPPORT
	sfmem_chip_select(1);
	sfmemc_nor_read_id(&vendor_id, &device_id);
	
	if (vendor_id == sfmem_stat.vendor_id 
			&& device_id == sfmem_stat.device_id) {
		sfmem_infol("Flash 0 Vendor[WINBOND], Device[W25Q128]");
	} else {
		sfmem_warningl("Flash 0 Vendor[0x%04x], Device[0x%04x]", 
				vendor_id, device_id);
		return 0;
	}
	sfmem_chip_select(0);
#endif

/*Register the driver.*/
	(void)sfmem_cdev_register(1);
	return 0;
}

static void __exit sfmem_exit(void)
{
	sfmem_debugl("Exit sfmem module.");

	/* unregister char device */
	sfmem_cdev_unregister(1);

	/* release the io mapping resource */
	if (!sfmem_stat.regs) {
		iounmap(sfmem_stat.regs);
		sfmem_stat.regs = NULL;
	}
	if (!sfmem_stat.base) {
		iounmap(sfmem_stat.base);
		sfmem_stat.base = NULL;
	}
}

late_initcall(sfmem_init);
module_exit(sfmem_exit);

