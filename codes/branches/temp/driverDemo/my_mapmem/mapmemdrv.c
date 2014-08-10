/*
Note:
For development:
1)Comment begin with XXX needs to check or others things to do.
*/

#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>
#include <linux/device.h>
/*XXX Any other include file???*/

#include "mapmemdrv.h"

/*Module Infomation*/
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("quiet_heart000@126.com");
MODULE_DESCRIPTION("This is a simple map memory module for map between virtual space and physical space.");
MODULE_ALIAS("map memory module");

/**
* @addtogroup mapmemdrv_group
*
* @{
*/

/**
* @name mapmemdrv_variable
* Private variables.
*/
/**
* @{
*/
static struct mapmem_dev g_dev;

static int mapmem_major = __MAPMEM_MAJOR__;

static const struct file_operations mapmem_fops = 
{
	.owner = THIS_MODULE,

	.llseek = mapmem_llseek,
	.read = mapmem_read,
	.write = mapmem_write,
	.mmap = mapmem_mmap, 
	.ioctl = mapmem_ioctl,
	.open = mapmem_open,
	.release = mapmem_release,
};
/**
* @}
*/

/**
* @name mapmemdrv_functions
* Private function declarations. 
*/
/**
* @{
*/
static int mapmem_open(struct inode *inode, struct file *filp);
static int mapmem_release(struct inode *inode, struct file *filp);
static ssize_t mapmem_read(struct file *filp, char __user *buf, 
							size_t count, loff_t *ppos);
static ssize_t mapmem_write(struct file *filp, const char __user *buf, 
							size_t count, loff_t *ppos);
static loff_t mapmem_llseek(struct file *filp, loff_t offset, int orig);
static int mapmem_mmap(struct file *filp, struct vm_area_struct *vma);
static int mapmem_ioctl(struct inode *inodep, struct file *filp, 
					unsigned int cmd, void __user *arg);
/**
* @{
*/

/**
* @}
*/

/*Private function implementations*/
static int mapmem_open(struct inode *inode, struct file *filp)
{
	filp->private_data = &g_dev;
	return 0;
}

static int mapmem_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t mapmem_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{
	printk(KERN_ALERT "read\n");
	/*struct mapmem_dev *dev = filp->private_data;//need or not*/

	unsigned long p = *ppos;
	int ret = 0;
	if(p > __MAPMEM_SIZE__)
	{
		printk(KERN_ALERT "some error1\n");
		return count ? -ENXIO:0;
	}
	if(count > __MAPMEM_SIZE__ - p)
	{
		count = __MAPMEM_SIZE__ - p;
	}

	if(copy_to_user(buf, (void*)(g_dev.mem_buf + p), count))
	{
		printk(KERN_ALERT "some error2\n");
		ret = -EFAULT;
	}
	else
	{
		*ppos += count;
		ret = count;
		printk(KERN_ALERT "read %d bytes(s) from %d\n", count, p);
	}
	return ret;
}

static ssize_t mapmem_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
	printk(KERN_ALERT "write!\n");
	/*struct mapmem_dev *dev = filp->private_data;//need or not*/

	unsigned long p = *ppos;
	int ret = 0;
	if(p > __MAPMEM_SIZE__)
	{
		return count ? -ENXIO:0;
	}
	if(count > __MAPMEM_SIZE__ -p)
	{
		count = __MAPMEM_SIZE__ - p;
	}
	if(copy_from_user(g_dev.mem_buf + p, buf, count))
	{
		ret = -EFAULT;
	}
	else
	{
		*ppos += count;
		ret = count;
		printk(KERN_ALERT "written %d bytes(s) from %d\n",count,p);
	}
	return ret;
}

static loff_t mapmem_llseek(struct file *filp, loff_t offset, int orig)
{
	printk(KERN_ALERT "llseek!\n");
	/*struct mapmem_dev *dev = filp->private_data;//need or not*/
	loff_t ret;
	switch(orig)
	{
		/*case 0:*/
		case SEEK_SET:
			if(offset < 0)
			{
				ret = -EINVAL;
				break;
			}
			if((unsigned int)offset > __MAPMEM_SIZE__)
			{
				ret = -EINVAL;
				break;
			}
			filp->f_pos = (unsigned int)offset;
			ret = filp->f_pos;
			break;
		/*case 1:*/
		case SEEK_CUR:
			if((filp->f_pos+offset) > __MAPMEM_SIZE__)
			{
				ret = -EINVAL;
				break;
			}
			if((filp->f_pos+offset) < 0)
			{
				ret = -EINVAL;
				break;
			}
			filp->f_pos += offset;
			ret = filp->f_pos;
			break;
		case SEEK_END:
			if(offset > 0)
			{
				ret = -EINVAL;
				break;
			}
			if(offset < -__MAPMEM_SIZE__)
			{
				ret = -EINVAL;
				break;
			}
			filp->f_pos = offset+__MAPMEM_SIZE__;
			ret = filp->f_pos;
			break;
		default:
			ret = -EINVAL;
	}
	return ret;
}

static int mapmem_mmap(struct file *filp, struct vm_area_struct *vma)
{
	/*struct mapmem_dev *dev = filp->private_data;//need or not*/
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
	unsigned long size = vma->vm_end - vma->vm_start;
	if(offset + size > __MAPMEM_SIZE__)
	{
		printk(__DEVICE_NAME__"mmap size too big\n");
		return -ENXIO;
	}
	offset = offset + __pa(g_dev.mem_buf);
	vma->vm_flags |= VM_LOCKED;
	if(remap_pfn_range(vma, vma->vm_start, offset >> PAGE_SHIFT, size, PAGE_SHARED))
	{
		printk(__DEVICE_NAME__"remap_pfn_range failed\n");
		return -ENXIO;
	}
	return 0;
}

static int mapmem_ioctl(struct inode *inodep, struct file *filp, unsigned int cmd, void __user *arg)
{
	printk(KERN_ALERT "ioctl!\n");
	/*struct mapmem_dev *dev = filp->private_data;//need or not*/
	switch(cmd)
	{
		case __MEM_PHY_BASE__:
			//*((unsigned long*)arg) = g_dev.mem_buf?__pa(g_dev.mem_buf):0;
			if(copy_to_user(arg, (void*)(&g_dev.mem_buf), sizeof(unsigned long)))
			{/* XXX ??? */
				printk(KERN_ALERT "some error2\n");
				ret = -EFAULT;
			}
		break;
		default:
		return -EINVAL;
	}

	return 0;
}

int mapmem_init(void)
{
	int result;
	dev_t devno = MKDEV(mapmem_major,0);

#if  __IS_STATIC_MAJOR__
	if(mapmem_major)
	{
		result = register_chrdev_region(devno, 1, __DEVICE_NAME__);
	}
	else
	{
#endif
		result = alloc_chrdev_region(&devno, 0,1, __DEVICE_NAME__);
		mapmem_major = MAJOR(devno);
#if  IS_STATIC_MAJOR
	}
#endif

	if(result < 0)
	{
		printk(KERN_ALERT "Error register mapmem result:%d\n", result);
		return result;
	}

	memset(&g_dev, 0, sizeof(struct mapmem_dev));

	/* XXX not zeroed??? */
	g_dev.mem_buf = __get_free_pages(GFP_KERNEL, get_order(__MAPMEM_SIZE__));
	if(!g_dev.mem_buf)
	{
		result = -ENOMEM;
		goto fail_malloc_buffer;
	}

	cdev_init(g_dev.cdev, &mapmem_fops);
	g_dev.cdev.owner = THIS_MODULE;
	if (cdev_add(&(g_dev.cdev), devno, 1))
	{
		printk(KERN_ALERT "Error for adding mapmem");
	}

	printk(KERN_ALERT "Hello,mapmem driver inserted,major number is %d\n", mapmem_major);

	return 0;

	fail_malloc_buffer:
	free_pages(g_dev.mem_buf,get_order(__MAPMEM_SIZE__));
	unregister_chrdev_region(devno,1);
	return result;
}

void mapmem_exit(void)
{
	cdev_del(g_dev.cdev);

	free_pages(g_dev.mem_buf,get_order(__MAPMEM_SIZE__));
	unregister_chrdev_region(MKDEV(mapmem_major, 0), 1);
}

module_init(mapmem_init);
module_exit(mapmem_exit);
