/*
Functions:
(0) Simple log functions controlled by macro.
(1) Support many devices with different minors but the same major.
(2) Judge the current kernel code version, and compare it to specified.
(3) ioctl function be implemented in many ways.
(4) Message buffer are arranged by kernel list.
(5) Keep device open reference count by atom variable.
(6) Block & Nonblock send/receive support by wait_queue.
*/
#include <linux/version.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/wait.h>

#if LINUX_VERSION_CODE>= KERNEL_VERSION(2,6,36)
#include <linux/slab.h>
#endif

#include <asm/uaccess.h>
#include <asm/atomic.h>

#include <linux/list.h>
#include "comm_drv.h"

#if 0
/*some files may be useful*/
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/vmalloc.h>
#include <linux/irqreturn.h>
#include <mach/irqs.h>
#include <asm/system.h>
#include <asm/io.h>
#endif


/*********Debug Flags************/
/*Debug switch: 1 to open otherwise close.*/
#ifndef COMM_DRV_DBG
#define COMM_DRV_DBG 1
#endif

#if COMM_DRV_DBG == 1
#if 0
#define COMMDRV_DBG_DYNREG /*Dynamic registe for debug*/
#endif
/*Log functions : It's best to use this to print log!!!*/
/*Example:
*print log:
*a)comm_info("your message.\n");
*b)comm_info("your string:%s, your integer:%d.\n",strvalue,intvalue);
*/
#define comm_printk(level, format, args...) \
    printk(level "[Kernel module: comm] %s() @%d ====>> " format, \
           __FUNCTION__, __LINE__, ##args)
#define comm_info(format, args...) \
    comm_printk(KERN_INFO, format , ##args)/*KERN_INFO*/
#define assert(s) do{if (!(s)) panic(#s);} while(0);
#else
#define comm_printk(level, format, args...) printk(level format, ## args)
#define comm_info(format, args...)
#define assert(s)
#endif

/*********Miscellaneous*********/
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("QuietHeart");
MODULE_DESCRIPTION("This module is used for communication with cpu1.");
MODULE_ALIAS("cpu1comm module");

/***********Declarations********/
#define comm_error(format, args...) \
    comm_printk(KERN_ERR, "Error! " format "\n" , ## args)

static int commdrv_open(struct inode* inode, struct file* filp);
static int commdrv_release(struct inode* inode, struct file* filp);
static ssize_t commdrv_read(struct file* filp, char __user* buf,
                                size_t count, loff_t* ppos);
static ssize_t commdrv_write(struct file* filp, const char __user* buf,
                                 size_t count, loff_t* ppos);
static loff_t commdrv_llseek(struct file* filp, loff_t offset, int orig);
static int commdrv_mmap(struct file* file, struct vm_area_struct* vma);
#if LINUX_VERSION_CODE>= KERNEL_VERSION(2,6,36)
static long commdrv_ioctl(struct file* filp, unsigned int cmd, unsigned long arg);
#else
static int commdrv_ioctl(struct inode* inodep, struct file* filp,
                             unsigned int cmd, unsigned long arg);
#endif

static int comm_register_devices(int minor_count);
static void comm_unregister_devices(int minor_count);
static void comm_initialize(void);
static int comm_alloc_buf(int minor, int nblks, int blksz);
static int comm_dealloc_buf(int minor);
static int comm_send_wb(int minor,const void __user* data, int count);
static int comm_receive_len(int minor);
static int comm_receive_rb(int minor, void __user* data, int count);

struct table_item
{
	struct list_head list;
	char *data;
	int length;
};

struct commdrv_dev
{
	/*XXX typedef*/
    struct cdev cd_cdev;

    /*other members use for driver*/
	atomic_t cd_refcount;
	unsigned cd_nblks;
	unsigned cd_blksz;

	/*char **cd_tblist;*/
	struct list_head cd_tlist;
	struct list_head *cd_tlist_readp;
	struct list_head *cd_tlist_writep;
	unsigned cd_tlist_full:1;
	unsigned cd_tlist_reserve:31;
	struct table_item *cd_items;

	/*concurrency*/
	wait_queue_head_t cd_wevent;
	wait_queue_head_t cd_revent;
};
static int comm_major = COMMDRV_MAJOR;
static struct commdrv_dev *devp;

static const struct file_operations commdrv_fops =
{
    .owner = THIS_MODULE,
    .llseek = commdrv_llseek,
    .read = commdrv_read,
    .write = commdrv_write,
    .mmap = commdrv_mmap,
#if LINUX_VERSION_CODE>= KERNEL_VERSION(2,6,36)
    .unlocked_ioctl = commdrv_ioctl,
#else
    .ioctl = commdrv_ioctl,
#endif
    .open = commdrv_open,
    .release = commdrv_release,
};



/*******Implementations********/
/***Internal***/
static int comm_register_devices(int minor_count)
{
	int ret;
	int i;

    dev_t devno;
    comm_info("\n");

	devno = MKDEV(comm_major, 0);
	devp = kmalloc(minor_count * sizeof(struct commdrv_dev), GFP_KERNEL);
	if(!devp)
	{
		comm_error("kmalloc for device structure failed!\n");
		ret = -ENOMEM;
		return ret;
	}
	memset(devp, 0, minor_count * sizeof(struct commdrv_dev));

	ret = register_chrdev_region(devno, minor_count, COMM_DEVICE);
	if (ret) {
		comm_error("register_chrdev_region() failed !! minor=%d\n", minor_count);
		return ret;
	}

	for (i = 0; i < minor_count; ++i)
	{
		devno = MKDEV(comm_major, i);
		cdev_init(&(devp[i].cd_cdev), &commdrv_fops);

		/*one device support only one minor.*/
		ret = cdev_add(&(devp[i].cd_cdev), devno, 1); 
		if (ret)
		{/*TODO undo previous register action.*/
			comm_error("cdev_add() failed !! minor=%d", minor_count);
			return ret;
		}
	}

	return 0;
}

static void comm_unregister_devices(int minor_count)
{
	int i;

    dev_t devno;
	devno = MKDEV(comm_major, 0);
    comm_info("\n");

	for (i = 0; i < minor_count; ++i)
	{
		cdev_del(&(devp[i].cd_cdev));
	}
	unregister_chrdev_region(devno, minor_count);

	if(!devp)
	{
		kfree(devp);
		devp = NULL; /*XXX*/
	}
}

static void comm_initialize(void)
{
	int i;
    comm_info("\n");
	for(i = 0; i < COMM_COUNT; ++i)
	{
		atomic_set(&devp[i].cd_refcount, 0);
		devp[i].cd_nblks = 0;
		devp[i].cd_blksz = 0;
		INIT_LIST_HEAD(&(devp[i].cd_tlist));
		devp[i].cd_tlist_readp = &devp[i].cd_tlist;
		devp[i].cd_tlist_writep = &devp[i].cd_tlist;
		devp[i].cd_tlist_full = 1;
		devp[i].cd_items = NULL;
		init_waitqueue_head(&devp[i].cd_wevent);
		init_waitqueue_head(&devp[i].cd_revent);
	}
}

static int comm_alloc_buf(int minor,int nblks, int blksz)
{/*XXX protect*/
	int i;
	int ret;

    comm_info("\n");
	ret = 0;
	assert(list_empty(&devp[minor].cd_tlist));
	devp[minor].cd_items = kmalloc(nblks * sizeof(struct table_item), GFP_KERNEL);
	if(!devp[minor].cd_items)
	{/*XXX protect release*/
		comm_error("kmalloc for talble blocks failed!\n");
		ret = -ENOMEM;
		return ret;
	}
	memset(devp[minor].cd_items, 0, nblks * sizeof(struct table_item));

	for(i = 0; i < nblks; ++i)
	{
		devp[minor].cd_items[i].data = kmalloc(blksz, GFP_KERNEL);
		if(!devp[minor].cd_items[i].data)
		{/*XXX protect release*/
			comm_error("kmalloc for talble block [%d]th's data failed!\n",i);
			ret = -ENOMEM;
			return ret;
		}
		memset(devp[minor].cd_items[i].data, 0, blksz);
		list_add_tail(&(devp[minor].cd_items[i].list),&devp[minor].cd_tlist);
	}
	devp[minor].cd_nblks = nblks;
	devp[minor].cd_blksz = blksz;
	devp[minor].cd_tlist_readp = devp[minor].cd_tlist.next;
	devp[minor].cd_tlist_writep = devp[minor].cd_tlist.next;
	devp[minor].cd_tlist_full = 0;
	return ret;
}

static int comm_dealloc_buf(int minor)
{/*XXX protect*/
	int ret;
	struct table_item *item;
	struct list_head *pos;
	struct list_head *pos2;

    comm_info("\n");
	ret = 0;
	assert(!list_empty(&devp[minor].cd_tlist));
	list_for_each_safe(pos, pos2, &devp[minor].cd_tlist)
	{
		item = list_entry(pos, struct table_item, list);
		kfree(item->data);
		item->data = NULL;
		list_del(pos);
	}
	devp[minor].cd_nblks = 0;
	devp[minor].cd_blksz = 0;
	devp[minor].cd_tlist_readp = &devp[minor].cd_tlist;
	devp[minor].cd_tlist_writep = &devp[minor].cd_tlist;
	devp[minor].cd_tlist_full = 1;
	kfree(devp[minor].cd_items);
	devp[minor].cd_items = NULL;
	return ret;
}

static int comm_send_wb(int minor, const void __user* data, int count)
{
	int sent;
	struct table_item *item;

    comm_info("\n");

	if(unlikely(count > devp[minor].cd_blksz))
	{/*XXX is it ok? block?*/
		comm_error("No space!\n");
		return -ENOSPC;
	}

	/*XXX check null?*/
	item = list_entry(devp[minor].cd_tlist_writep, struct table_item, list);

	sent = count;
	count = copy_from_user(item->data, data, count);
	sent -= count;
	if(unlikely(0 != count))
	{
		comm_error("send data error, sent: %d, remain: %d!\n", sent, count);
		return -ENOSPC;
	}

	if(likely(count == 0 && sent > 0))
	{
		item->length = sent;
		devp[minor].cd_tlist_writep = devp[minor].cd_tlist_writep->next;
		if(devp[minor].cd_tlist_writep == &devp[minor].cd_tlist)
		{
			devp[minor].cd_tlist_writep = devp[minor].cd_tlist_writep->next;
		}
		if(devp[minor].cd_tlist_writep == devp[minor].cd_tlist_readp)
		{
			devp[minor].cd_tlist_full = 1;
		}
	}
	return sent;
}

static int comm_receive_len(int minor)
{
	struct table_item *item;

    comm_info("\n");
	/*XXX check null?*/
	item = list_entry(devp[minor].cd_tlist_readp, struct table_item, list);
	return item->length;
}

static int comm_receive_rb(int minor, void __user* data, int count)
{
	int received;
	struct table_item *item;

    comm_info("\n");

	if((!devp[minor].cd_tlist_full 
				&& (devp[minor].cd_tlist_writep == devp[minor].cd_tlist_readp))
			|| unlikely(count > devp[minor].cd_blksz))
	{/*XXX is it ok?*/
		comm_error("Empty buffer!\n");
		return -EAGAIN;
	}

	/*XXX check null?*/
	item = list_entry(devp[minor].cd_tlist_readp, struct table_item, list);

	received = count;
	count = copy_to_user(data, item->data, count);
	received -= count;
	if(unlikely(0 != count))
	{
		comm_error("receive data error, received: %d, remain: %d!\n", 
				received, count);
		return -EAGAIN;
	}

	if(likely(count == 0 && received > 0))
	{
		devp[minor].cd_tlist_readp = devp[minor].cd_tlist_readp->next;
		if(devp[minor].cd_tlist_readp == &devp[minor].cd_tlist)
		{
			devp[minor].cd_tlist_readp = devp[minor].cd_tlist_readp->next;
		}
		devp[minor].cd_tlist_full = 0;
	}
	return received;
}

/***Driver Interface***/
static int commdrv_open(struct inode* inodep, struct file* filp)
{
	int minor;
    comm_info("\n");
	minor = MINOR(inodep->i_cdev->dev);
	filp->private_data = &devp[minor];
	atomic_inc(&devp[minor].cd_refcount);
    comm_info("minor is :%d\n",minor);
	return 0;
}

static int commdrv_release(struct inode* inodep, struct file* filp)
{
	int minor;

    comm_info("\n");
	minor = MINOR(inodep->i_cdev->dev);
	assert(atomic_read(&devp[minor].cd_refcount) > 0);
	if(atomic_dec_and_test(&devp[minor].cd_refcount))
	{
		comm_info("The last reference, dealloc the table block buffer!\n");
		if(likely(NULL != devp[minor].cd_items))
		{
			comm_dealloc_buf(minor);
		}
	}
	return 0;
}
static ssize_t commdrv_read(struct file* filp, char __user* buf,
		size_t count, loff_t* ppos)
{
    comm_info("\n");
#if 0
    struct cpu1commdrv_dev* dev;
    char* rbuf;
    int ret;
    dev = filp->private_data;
    cpu1comm_info("\n");
    rbuf = (char*)vmalloc(count);
    if(!rbuf) {
        cpu1comm_error("vmalloc failed!");
        return 0;
    }
    do { /*XXX another kthread???*/
        count -= receive_rb(rbuf, count);
        notify_write();
        wait_for_receive();
    } while(count > 0);
    ret = copy_to_user((char __user*)buf, rbuf, count);
    if(0 != ret) {
        cpu1comm_error("copy to user error %d!", ret);
        vfree(rbuf);
        return 0;
    }
    vfree(rbuf);
    return count;
#endif
	return 0;
}

static ssize_t commdrv_write(struct file* filp, const char __user* buf,
		size_t count, loff_t* ppos)
{
    comm_info("\n");
#if 0
    struct cpu1commdrv_dev* dev;
    char* wbuf;
    int tmp;
    int ret;
    dev = filp->private_data;
    cpu1comm_info("write!\n");
    wbuf = (char*)vmalloc(count);
    if(!wbuf) {
        cpu1comm_error("vmalloc failed!");
        return 0;
    }
    ret = copy_from_user(wbuf, (const char __user*)buf, count);
    if(0 != ret) {
        cpu1comm_error("copy from user error %d!", ret);
        vfree(wbuf);
        return 0;
    }
    set_cpu1_wlength(count);
    do { /*XXX another kthread???*/
        tmp = send_wb(wbuf, count);
        count -= tmp;
        ret += tmp;
        notify_read();
        wait_for_send();
    } while(count > 0);
    vfree(wbuf);
    return ret;
#endif
	return 1;
}

static loff_t commdrv_llseek(struct file* filp, loff_t offset, int orig)
{
    comm_info("\n");
	return 0;
}

static int commdrv_mmap(struct file* file, struct vm_area_struct* vma)
{
    comm_info("\n");

#if 0
    long phy_addr;
    unsigned long offset;
    unsigned long size;
    vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
    vma->vm_flags |= VM_LOCKED;
    offset = vma->vm_pgoff << PAGE_SHIFT;/*XXX assume is 12*/
    size = vma->vm_end - vma->vm_start;
    if(BUF0_OFF == offset) {
        /*XXX Should check the size from user space equals to the real size defined in kernel.
        * And if the phy_addr is page ajustment.*/
        phy_addr = (long)devp->cd_wkram.write_buf - DIABLO_WORKRAM_VIRT_BASE + DIABLO_WORKRAM_PHYS_BASE;
        cpu1comm_info("map buffer0 orig 0x%x\n", RB_DIABLO_WKRAM_HANDSHAKE_BUF0);
        cpu1comm_info("map buffer0 0x%x\n", phy_addr);
    } else if(BUF1_OFF == offset) {
        /*XXX Should check the size from user space equals to the real size defined in kernel.
        * And if the phy_addr is page ajustment.*/
        phy_addr = (long)devp->cd_wkram.read_buf - DIABLO_WORKRAM_VIRT_BASE + DIABLO_WORKRAM_PHYS_BASE;
        cpu1comm_info("map buffer1 orig 0x%x\n", RB_DIABLO_WKRAM_HANDSHAKE_BUF1);
        cpu1comm_info("map buffer1 0x%x\n", phy_addr);
    } else if(START_OFF == offset) {
        /*XXX Should check the size from user space equals to the real size defined in kernel.
        * And if the phy_addr is page ajustment.*/
        phy_addr = DIABLO_WORKRAM_PHYS_BASE;
    } else {
        cpu1comm_error(" Unknown memory map offset!\n");/*XXX*/
        return -ENXIO;
    }
    /*phy_addr must be 4k *n*/
    cpu1comm_info("Page shift %d,map buffer phy_addr shift:0x%x\n", PAGE_SHIFT, phy_addr >> PAGE_SHIFT);
    if(remap_pfn_range(vma, vma->vm_start, phy_addr >> PAGE_SHIFT, size, vma->vm_page_prot)) {
        cpu1comm_error(" remap_pfn_range failed\n");/*XXX*/
        return -ENXIO;
    }
#endif
    return 0;
}

#if LINUX_VERSION_CODE>= KERNEL_VERSION(2,6,36)
static long commdrv_ioctl(struct file* filp, unsigned int cmd, unsigned long arg)
#else
static int commdrv_ioctl(struct inode* inodep, struct file* filp,
		unsigned int cmd, unsigned long arg)
#endif
{
	int minor;
	int ret;

	TABLE_INFO iarg_tbl;
	int tbl_nblks;
	int tbl_blksz;

	DATA_BUF iarg_dbf;
	DATA_BUF oarg_dbf;
	void __user* dbf_data; 
	int dbf_len;
#if 0
    struct commdrv_dev* dev;
#endif

    comm_info("\n");
#if 0
    dev = filp->private_data;
#endif

#if LINUX_VERSION_CODE>= KERNEL_VERSION(2,6,36)
	minor = MINOR(filp->f_dentry->d_inode->i_cdev->dev);
#else
	minor = MINOR(inodep->i_cdev->dev);/*XXX replaced by dev?*/
#endif
	ret = 0;

    comm_info("_IOC_TYPE:%c\n", _IOC_TYPE(cmd));
	if(_IOC_TYPE(cmd) != COMM_MAGIC)
	{
		return -ENOTTY;
	}

    comm_info("_IOC_NR:%d\n", _IOC_NR(cmd));
	if(_IOC_NR(cmd) > COMM_IOC_MAXNR)
	{
		return -ENOTTY;
	}

#if 0
	if (_IOC_DIR(cmd) & _IOC_READ)
	{
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	}
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
	{
		err = !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	}
	if (err)
	{
		return -EFAULT;
	}
#endif

    switch(cmd) {
    case COMM_CREAT:
		comm_info("COMM_CREAT command.\n");
		if(likely(NULL == devp[minor].cd_items))
		{
			ret = copy_from_user(&iarg_tbl, (const void __user*)arg, 
					sizeof(TABLE_INFO));
			if(0 != ret)
			{
				comm_error("copy input from user error %d!", ret);
				return ret;
			}

			tbl_nblks = iarg_tbl.ti_nblks;
			tbl_blksz = iarg_tbl.ti_blksz;
			comm_info("table block count: %d\n, table block size:%d\n", 
					tbl_nblks, tbl_blksz);
			comm_alloc_buf(minor,tbl_nblks,tbl_blksz);
		}
		else
		{
            comm_error("Be created more than one time.\n");
			ret = -EBUSY;
			return ret;
		}
        break;
	case COMM_SEND:
		comm_info("COMM_SEND command.\n");
        ret = copy_from_user(&iarg_dbf, 
				(const void __user*)arg, sizeof(DATA_BUF));
        if(unlikely(0 != ret))
		{
            comm_error("copy input from user error %d!", ret);
			return ret;
        }

		dbf_len = iarg_dbf.length;
#if 0
		dbf_data = (char*)vmalloc(dbf_len);/*XXX no need this copy.*/
		if(!dbf_data)
		{
			comm_error("vmalloc dbf_data is NULL!");
			ret = -ENOMEM;
			return ret;
		}
        ret = copy_from_user(dbf_data, 
				(const void __user*)iarg_dbf.data, dbf_len);
        if(0 != ret)
		{
            comm_error("copy input from user error %d!", ret);
			vfree(dbf_data);
			return ret;
        }
		comm_info("send length is:%d,\n send data is:%s.\n",
				dbf_len, dbf_data);
		vfree(dbf_data);
#endif
		dbf_data = iarg_dbf.data;

		if(devp[minor].cd_tlist_full)
		{
			if(filp->f_flags & O_NONBLOCK)
			{
				comm_error("Buffer full!\n");
				return -EAGAIN;
			}
			if(wait_event_interruptible(devp[minor].cd_revent, !devp[minor].cd_tlist_full))
			{
				comm_error("Signal caught!\n");
				return -ERESTARTSYS;
			}
		}

		ret = comm_send_wb(minor, dbf_data, dbf_len);
		if(ret < 0)
		{/*XXX*/
			comm_info("Cann't send all the data at one time.\n");
			return ret;
		}

		if(!(filp->f_flags & O_NONBLOCK))
		{
			wake_up_interruptible(&devp[minor].cd_wevent);
		}
        break;
	case COMM_GETLEN:
		/*TODO*/
		comm_info("COMM_GETLEN command.\n");
		if((!devp[minor].cd_tlist_full 
					&& (devp[minor].cd_tlist_writep == devp[minor].cd_tlist_readp)))
		{
			comm_error("Empty buffer!\n");
			if(filp->f_flags & O_NONBLOCK)
			{
				return -EAGAIN;
			}
			if(wait_event_interruptible(devp[minor].cd_wevent,
						((devp[minor].cd_tlist_writep != devp[minor].cd_tlist_readp) 
						 || devp[minor].cd_tlist_full)))
			{
				comm_error("Signal caught!\n");
				return -ERESTARTSYS;
			}
		}
		else
		{
			ret = comm_receive_len(minor);
		}
		comm_info("get length is: %d\n", ret);
        break;
	case COMM_RECEIVE:
		comm_info("COMM_RECEIVE command.\n");
        ret = copy_from_user(&oarg_dbf, 
				(const void __user*)arg, sizeof(DATA_BUF));
        if(unlikely(0 != ret))
		{
            comm_error("copy output from user error %d!", ret);
			return ret;
        }
		dbf_len = oarg_dbf.length;
		dbf_data = oarg_dbf.data;

		ret = comm_receive_rb(minor, dbf_data, dbf_len);
		if(ret < 0)
		{/*XXX*/
			comm_info("Cann't receive all the data at one time.\n");
			return ret;
		}

		if(!(filp->f_flags & O_NONBLOCK))
		{
			wake_up_interruptible(&devp[minor].cd_revent);
		}
        break;
	case COMM_CLEAR:
		comm_info("COMM_CLEAR command.\n");
        break;
	default:
		comm_info("Unknown command.\n");
	}

	/*XXX return to userspace?*/
    return ret;
}

static int commdrv_init(void)
{/*XXX Error check.*/
    int result;
    comm_info("\n");

	result = comm_register_devices(COMM_COUNT);
	comm_initialize();

    return result;
}

static void commdrv_exit(void)
{
    comm_info("\n");

	comm_unregister_devices(COMM_COUNT);
}

module_init(commdrv_init);
module_exit(commdrv_exit);
