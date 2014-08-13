#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/vmalloc.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>

#include <linux/irqreturn.h>
#include <mach/irqs.h>

#include "cpu1comm_drv.h"

/*********Debug Flags************/
/*Debug switch: 1 to open otherwise close.*/
#define CPU1COMM_DBG 1

#if CPU1COMM_DBG == 1
//#define CPU1COMMDRV_DBG_DYNREG /*Dynamic registe for debug*/

/*Log functions : It's best to use this to print log!!!*/
/*Example:
*print log:
*a)cpu1comm_info("your message.\n");
*b)cpu1comm_info("your string:%s, your integer:%d.\n",strvalue,intvalue);
*/
#define cpu1comm_printk(level, format, args...) \
	printk(level "[CPU1COMM] %s() @%d ====>> " format, \
			__FUNCTION__, __LINE__, ##args)
#define cpu1comm_info(format, args...) \
	cpu1comm_printk(KERN_INFO, format , ##args)/*KERN_INFO*/
#else
/*#define cpu1comm_printk(level, format, ...) printk(level format, __VA_ARGS__)*/
#define cpu1comm_printk(level, format, args...) printk(level format, ## args)
#define cpu1comm_info(format, args...)
#endif

/*********Miscellaneous*********/
MODULE_DESCRIPTION("This module is used for communication with cpu1.");
MODULE_ALIAS("cpu1comm module");

struct cpu1commdrv_dev
{
	struct cdev cd_cdev;
	/*other members use for driver*/
	int other;
};

#define cpu1comm_error(format, args...) \
	cpu1comm_printk(KERN_ERR, "Error! " format "\n" , ## args)
/***********Declarations********/
static int cpu1commdrv_open(struct inode *inode, struct file *filp);
static int cpu1commdrv_release(struct inode *inode, struct file *filp);
static ssize_t cpu1commdrv_read(struct file *filp, char __user *buf, 
		size_t count, loff_t *ppos);
static ssize_t cpu1commdrv_write(struct file *filp, const char __user *buf, 
		size_t count, loff_t *ppos);
static loff_t cpu1commdrv_llseek(struct file *filp, loff_t offset, int orig);
static int cpu1commdrv_mmap(struct file *file, struct vm_area_struct *vma);
static int cpu1commdrv_ioctl(struct inode *inodep, struct file *filp, 
		unsigned int cmd, unsigned long arg);

#ifdef CPU1COMMDRV_DBG_DYNREG
static int cpu1commdrv_major = CPU1COMMDRV_MAJOR;
#else
static int cpu1commdrv_major = CPU1COMMDRV_MAJOR;
static struct cpu1commdrv_dev cpu1comm_dev;
#endif
static struct cpu1commdrv_dev *devp;


/*******Implementations********/
/***Internal***/
static irqreturn_t data_intr (int irq, void *devId);
static int init_irq();
static int init_other();
static int clear_other();
static int notify();

/*XXX receive notify from cpu1.*/
static irqreturn_t data_intr (int irq, void *devId)
{
	cpu1comm_info("\n");
	return IRQ_HANDLED;/*XXX IRQ_NONE for share.*/
}


/*XXX init the interrupt handler.*/
static int init_irq()
{
	cpu1comm_info("\n");
	int rtn = 0;
	/*
	rtn = request_irq(NUMBER_OF_IRQ, (irq_handler_t)data_intr, 0, CPU1COMM_DEVICE, NULL);
	if(rtn != 0)
	{
		cpu1comm_error("request_irq:DIABLO_HANDSHAKE_RECV_IRQ,failed!%d\n",rtn);
		free_irq(CPU0_HANDSHAKE_RECV_IRQ, NULL);
		return rtn;
	}
	*/
	/*TODO */
	return rtn;
}

/*init for hand shake.*/
static int init_other()
{
	cpu1comm_info("\n");
	init_irq();
	/*TODO */
	return 0;
}

/*close hand shake*/
static int clear_other()
{
	cpu1comm_info("\n");
    /*free_irq(NUMBER_OF_IRQ, NULL);*/
	/*TODO*/
	return 0;
}

static int notify()
{
	cpu1comm_info("\n");
	return 0;
}

/*TODO */
static int cpu1commdrv_open(struct inode *inode, struct file *filp)
{
	cpu1comm_info("\n");
	filp->private_data = devp;
	return 0;
}

/*TODO */
static int cpu1commdrv_release(struct inode *inode, struct file *filp)
{
	cpu1comm_info("\n");
	return 0;
}

/*TODO */
/*Note: need a copy from user space to kernel space.*/
static ssize_t cpu1commdrv_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{
	struct cpu1commdrv_dev *dev;
	char *rbuf;
	int ret;
	cpu1comm_info("\n");
	dev = filp->private_data;
	rbuf = (char*)vmalloc(count);
	if(!rbuf)
	{
		cpu1comm_error("vmalloc failed!");
		return 0;
	}
	ret = copy_to_user((char __user*)buf, rbuf, count);
	if(0 != ret)
	{
		cpu1comm_error("copy to user error %d!", ret);
		vfree(rbuf);
		return 0;
	}
	vfree(rbuf);
	return count;
}

/*TODO */
/*Note: need a copy from user space to kernel space.*/
static ssize_t cpu1commdrv_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
	struct cpu1commdrv_dev *dev;
	char *wbuf;
	int tmp;
	int ret;
	cpu1comm_info("\n");
	dev = filp->private_data;

	wbuf = (char*)vmalloc(count);
	if(!wbuf)
	{
		cpu1comm_error("vmalloc failed!");
		return 0;
	}
	ret = copy_from_user(wbuf, (const char __user*)buf, count);
	if(0 != ret)
	{
		cpu1comm_error("copy from user error %d!", ret);
		vfree(wbuf);
		return 0;
	}
	vfree(wbuf);
	return ret;
}

/*TODO */
static loff_t cpu1commdrv_llseek(struct file *filp, loff_t offset, int orig)
{
	cpu1comm_info("\n");
	return 0;
}

/*TODO */
static int cpu1commdrv_ioctl(struct inode *inodep, struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct cpu1commdrv_dev *dev;
	dev = filp->private_data;
	cpu1comm_info("ioctl!\n");
	switch(cmd)
	{/*XXX param check*/
#if 0
		case CPU1COMM_INIT:
			break;
		case CPU1COMM_RELEASE:
			break;
#endif
		case CPU1COMM_FAKE_WWRITE:
			{
				IOCTL_BUF iarg;/*from user (as 'input')*/
				char *buf;
				int ret;

				/*get param data from user.*/
				ret = copy_from_user(&iarg, (const void __user*)arg, sizeof(IOCTL_BUF));
				if(0 != ret)
				{
					cpu1comm_error("copy from user error %d!", ret);
				}
				cpu1comm_info("data length from user (for 'write') is:%d\n", iarg.length);

				/*Note:copy again for real data because iarg.data is user virtual address.*/
				buf = (char*)vmalloc(iarg.length);
				if(!buf)
				{
					cpu1comm_error("vmalloc failed!");
					return 0;
				}
				cpu1comm_info("input address of iarg.data(user virtual address) 0x%x\n", iarg.data);
				copy_from_user(buf,(const void __user*)iarg.data, iarg.length);
				cpu1comm_info("data from user (for 'write') is:%s\n", buf);/*assume data is string.*/
				vfree(buf);
			}
			break;
		case CPU1COMM_FAKE_WREAD:
			{
				IOCTL_BUF oarg;/*also store data copy to user(oarg.data as 'output')*/
				char *buf;
				int ret;
				int i;

				
				/*length of data required by user.*/
				ret = copy_from_user(&oarg, (const void __user*)arg, sizeof(IOCTL_BUF));
				if(0 != ret)
				{
					cpu1comm_error("copy from user error %d!", ret);
				}
				buf = (char*)vmalloc(oarg.length);
				if(!buf)
				{
					cpu1comm_error("vmalloc failed!");
					return 0;
				}
				cpu1comm_info("data length required from user is:%d\n",oarg.length);

				/*make data and copy it to user.*/
				for(i = 0; i < oarg.length - 1; ++i)
				{
					buf[i] = 'A' + i % 26;
				}
				cpu1comm_info("data to user(for 'read') is:%s\n",buf);

				/*Note:don't copy by memcpy because iarg.data is user virtual address.*/
				ret = copy_to_user((void __user*)oarg.data, buf, oarg.length);
				if(0 != ret)
				{
					cpu1comm_error("copy to user error %d!", ret);
				}
				vfree(buf);
			}
			break;
		case CPU1COMM_NOTIFY_READ:
			notify();
			break;
#if 0
		case CPU1COMM_WAIT_FOR_SEND:
			wait_for_send();
			break;
		case CPU1COMM_NOTIFY_WRITE:
			notify_write();
			break;
		case CPU1COMM_WAIT_FOR_RECEIVE:
			wait_for_receive();
			break;
		case CPU1COMM_SEND:
			{
				int count;
				char *buf;
				int ret;
				IOCTL_BUF iarg;/*XXX copy to user*/
				ret = copy_from_user(&iarg, (const void __user*)arg, sizeof(IOCTL_BUF));
				if(0 != ret)
				{
					cpu1comm_error("copy from user error %d!", ret);
				}
				count = iarg.length;
				buf = iarg.data;
				cpu1comm_info("input size is:%d\n",count);
				set_cpu1_wlength(count);
				do{/*XXX another kthread???*/
					wait_for_send();
					count -= send_wb(buf, count);
					notify_read();
				}while(count > 0);
			}
			break;
		case CPU1COMM_RECEIVE:
			{
				int count;
				char *buf;
				int ret;
				IOCTL_BUF oarg;/*XXX copy to user*/
				ret = copy_from_user(&oarg, (const void __user*)arg, sizeof(IOCTL_BUF));
				if(0 != ret)
				{
					cpu1comm_error("copy from user error %d!", ret);
				}
				count = oarg.length;/*XXX copy to user*/
				buf = oarg.data;
				cpu1comm_info("input size is:%d\n",count);
				do{/*XXX another kthread???*/
					wait_for_receive();
					count -= receive_rb(buf, count);	/*TODO only receive data before empty???*/
					notify_write();
				}while(count > 0);
				ret = copy_to_user((void __user*)arg, &oarg, sizeof(IOCTL_BUF));
				if(0 != ret)
				{
					cpu1comm_error("copy to user error %d!", ret);
				}
			}
			break;
		case CPU1COMM_WKRAM_SBUF:
			break;
		case CPU1COMM_WKRAM_RBUF:
			break;
		case CPU1COMM_WKRAM_RCVWAIT:
			{
				int rcv_stat;
				rcv_stat = get_cpu1_rstatus();
				if(1 == rcv_stat || devp->cd_wkram.read_buf_wp == devp->cd_wkram.read_buf_rp)
				{/*XXX empty.*/
					wait_for_receive();
				}
			}
			break;
		case CPU1COMM_SYNC_KRAM:
			{
				/*sync the wkram pointer by user.*/
				int ret;
				ret = 0;
				CPU_COMM_RAM usr_wkram;
				ret = copy_from_user(&usr_wkram, (const void __user*)arg, sizeof(CPU_COMM_RAM));
				if(0 != ret)
				{
					cpu1comm_error("copy from user error %d!", ret);
				}
				devp->cd_wkram.write_buf_wp = (long)usr_wkram.write_buf_wp - (long)usr_wkram.write_buf
					+ (long)devp->cd_wkram.write_buf;
				devp->cd_wkram.write_buf_rp = (long)usr_wkram.write_buf_rp - (long)usr_wkram.write_buf
					+ (long)devp->cd_wkram.write_buf;
				devp->cd_wkram.read_buf_wp = (long)usr_wkram.read_buf_wp - (long)usr_wkram.read_buf
					+ (long)devp->cd_wkram.read_buf;
				devp->cd_wkram.read_buf_rp = (long)usr_wkram.read_buf_rp - (long)usr_wkram.read_buf
					+ (long)devp->cd_wkram.read_buf;
			}
			break;
		case CPU1COMM_SYNC_URAM:
			{
				/*sync the wkram pointer by user.*/
				int ret;
				ret = 0;
				CPU_COMM_RAM usr_wkram;
				ret = copy_from_user(&usr_wkram, (const void __user*)arg, sizeof(CPU_COMM_RAM));
				if(0 != ret)
				{
					cpu1comm_error("copy from user error %d!", ret);
				}
				usr_wkram.write_buf_wp = (long)devp->cd_wkram.write_buf_wp - (long)devp->cd_wkram.write_buf
					+ (long)usr_wkram.write_buf;
				usr_wkram.write_buf_rp = (long)devp->cd_wkram.write_buf_rp - (long)devp->cd_wkram.write_buf
					+ (long)usr_wkram.write_buf;
				usr_wkram.read_buf_wp = (long)devp->cd_wkram.read_buf_wp - (long)devp->cd_wkram.read_buf
					+ (long)usr_wkram.read_buf;
				usr_wkram.read_buf_rp = (long)devp->cd_wkram.read_buf_rp - (long)devp->cd_wkram.read_buf
					+ (long)usr_wkram.read_buf;
				ret = copy_to_user((void __user*)arg, &usr_wkram, sizeof(CPU_COMM_RAM));
				if(0 != ret)
				{
					cpu1comm_error("copy to user error %d!", ret);
				}
			}
			break;
		case CPU1COMM_WWRITE_TEST:
			devp->cd_wkram.write_buf->data[0] = WWRITE_CHAR1;
			devp->cd_wkram.read_buf->data[0] = WWRITE_CHAR2;
			break;
		case CPU1COMM_RWRITE_TEST:
			cpu1comm_info("buf0address:0x%x,buf0[0]:%c\n",
					devp->cd_wkram.write_buf->data,devp->cd_wkram.write_buf->data[0]);
			cpu1comm_info("buf0's r pointer address:0x%x,buf0[0]:%c\n",
					devp->cd_wkram.write_buf_rp,devp->cd_wkram.write_buf_rp[0]);
			cpu1comm_info("buf1address:0x%x,buf1[0]:%c\n",
					devp->cd_wkram.read_buf->data,devp->cd_wkram.read_buf->data[0]);
			cpu1comm_info("buf1's r pointer address:0x%x,buf1[0]:%c\n",
					devp->cd_wkram.read_buf_rp,devp->cd_wkram.read_buf_rp[0]);
			break;
#endif
		default:
			break;
	}
	return 0;
}

static int cpu1commdrv_mmap(struct file *file, struct vm_area_struct *vma)
{
	/*XXX How to map phy address:[RB_DIABLO_WKRAM_HANDSHAKE_BUF0,RB_DIABLO_WKRAM_BSPLOGREC_ADR]*/
	/*XXX Should adjust offset by physic address, not this way.*/
	cpu1comm_info("\n");
	cpu1comm_info("base addr by _pa:0x%x, by macro:0x%x\n",__pa(DIABLO_WORKRAM_VIRT_BASE),
			DIABLO_WORKRAM_PHYS_BASE);
	cpu1comm_info("mmap offset:%d\n",vma->vm_pgoff);/*alread right shift by kernel.*/
	long phy_addr;
	unsigned long offset;
	unsigned long size;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_flags |= VM_LOCKED;
	offset = vma->vm_pgoff << PAGE_SHIFT;/*XXX assume is 12*/
	size = vma->vm_end - vma->vm_start;

	if(BUF0_OFF == offset)
	{
		/*XXX Should check the size from user space equals to the real size defined in kernel.
		* And if the phy_addr is page ajustment.*/
		phy_addr = (long)devp->cd_wkram.write_buf - DIABLO_WORKRAM_VIRT_BASE + DIABLO_WORKRAM_PHYS_BASE;
		cpu1comm_info("map buffer0 orig 0x%x\n", RB_DIABLO_WKRAM_HANDSHAKE_BUF0);
		cpu1comm_info("map buffer0 0x%x\n", phy_addr);
	}
	else if(BUF1_OFF == offset)
	{
		/*XXX Should check the size from user space equals to the real size defined in kernel.
		* And if the phy_addr is page ajustment.*/
		phy_addr = (long)devp->cd_wkram.read_buf - DIABLO_WORKRAM_VIRT_BASE + DIABLO_WORKRAM_PHYS_BASE;
		cpu1comm_info("map buffer1 orig 0x%x\n", RB_DIABLO_WKRAM_HANDSHAKE_BUF1);
		cpu1comm_info("map buffer1 0x%x\n", phy_addr);
	}
	else if(START_OFF == offset)
	{
		/*XXX Should check the size from user space equals to the real size defined in kernel.
		* And if the phy_addr is page ajustment.*/
		phy_addr = DIABLO_WORKRAM_PHYS_BASE;
	}
	else
	{
		cpu1comm_error(" Unknown memory map offset!\n");/*XXX*/
		return -ENXIO;
	}
	/*phy_addr must be 4k *n*/
	cpu1comm_info("Page shift %d,map buffer phy_addr shift:0x%x\n", PAGE_SHIFT,phy_addr>>PAGE_SHIFT);
	if(remap_pfn_range(vma, vma->vm_start, phy_addr >> PAGE_SHIFT, size, vma->vm_page_prot))
	{
		cpu1comm_error(" remap_pfn_range failed\n");/*XXX*/
		return -ENXIO;
	}

	return 0;
}

int cpu1commdrv_init(void)
{
	int result;
	int err;
	cpu1comm_info("\n");
	dev_t devno = MKDEV(cpu1commdrv_major,0);
#ifdef CPU1COMMDRV_DBG_DYNREG
	result = alloc_chrdev_region(&devno, 0,1, CPU1COMM_DEVICE);
	cpu1commdrv_major = MAJOR(devno);
#else
	cpu1comm_info("\n");
	result = register_chrdev_region(devno, 1, CPU1COMM_DEVICE);
#endif
	if(result < 0)
	{
		cpu1comm_error(" Register cpu1commdrv result:%d\n", result);/*XXX*/
		goto register_fail;
	}
	cpu1comm_info("sizeof(struct cpu1commdrv_dev):%d, sizeof(CPU_COMM_RAM):%d,major is:%d\n",
			sizeof(struct cpu1commdrv_dev),sizeof(CPU_COMM_RAM),MAJOR(devno));
#ifdef CPU1COMMDRV_DBG_DYNREG
	devp = kmalloc(sizeof(struct cpu1commdrv_dev),GFP_KERNEL);
	if(!devp)
	{
		result = -ENOMEM;
		goto malloc_fail;
	}
#else
	devp = &cpu1comm_dev;
#endif
	memset(devp, 0, sizeof(struct cpu1commdrv_dev));
	cdev_init(&devp->cd_cdev, &cpu1commdrv_fops);
	devp->cd_cdev.owner = THIS_MODULE;
	err = cdev_add(&devp->cd_cdev, devno, 1);
	if(err)
	{
		cpu1comm_error("Error %d adding cpu1commdrv", err);/*XXX*/
		goto add_fail;
	}
	
	init_other();/*XXX */
	return result;

/*error case*/
add_fail:
#ifdef CPU1COMMDRV_DBG_DYNREG
	;
malloc_fail:
#endif
	unregister_chrdev_region(devno,1);
register_fail:
	;
	return result;
}
void cpu1commdrv_exit(void)
{
	cpu1comm_info("\n");
	cdev_del(&devp->cd_cdev);
#ifdef CPU1COMMDRV_DBG_DYNREG
	kfree(devp);
	unregister_chrdev_region(MKDEV(cpu1commdrv_major, 0), 1);
#else
	unregister_chrdev_region(MKDEV(CPU1COMMDRV_MAJOR,0), 1);
#endif
	clear_other();
}

module_init(cpu1commdrv_init);
module_exit(cpu1commdrv_exit);
