/*一、功能：本例子是一个没有任何功能最简单的设备驱动例子，只有代码注释也很少。
 *目的就是在已经知道相关驱动知识的前提下便于编程查阅。

 *二、一般驱动简易使用说明：
 *1)编译
 *$make
 *2)插入模块
 *insmod simpledrv_std.ko
 *可以通过"cat /proc/devices"得知设备的主从号码
 *3)创建设备文件
 *#mknod mytest c <主设备号> 0
 *4)使用
 *写入数据：echo hello >mytest
 *读取数据：cat mytest
 *ioctl：需要自己编写测试程序进行测试。
 *5)卸载模块
 *rmmod simpledrv_std

 *查看驱动信息：
 $modinfo simpledrv_std.ko
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


#define simpledrv_SIZE 0x1000
#define simpledrv_MAJOR 1025

/*驱动模块信息*/
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Quiet Heart");
MODULE_DESCRIPTION("This is a simple global memory module.");
MODULE_ALIAS("global memory module");

/*simpledrv设备结构体*/
struct simpledrv_dev
{
	struct cdev cdev;

	/*用户自定义数据*/
	unsigned char mem[simpledrv_SIZE];
};

/*声明自定义驱动接口函数*/
int simpledrv_open(struct inode *inode, struct file *filp);
int simpledrv_release(struct inode *inode, struct file *filp);
static ssize_t simpledrv_read(struct file *filp, char __user *buf, 
							size_t count, loff_t *ppos);
static ssize_t simpledrv_write(struct file *filp, const char __user *buf, 
							size_t count, loff_t *ppos);
static loff_t simpledrv_llseek(struct file *filp, loff_t offset, int orig);
static int simpledrv_ioctl(struct inode *inodep, struct file *filp, 
					unsigned int cmd, unsigned long arg);

/*声明驱动实现需要的结构和变量*/
static int simpledrv_major = simpledrv_MAJOR;
struct simpledrv_dev *devp;

/*与字符设备结构体操作相关的函数指针结构体*/
static const struct file_operations simpledrv_fops = 
{
	.owner = THIS_MODULE,

	.llseek = simpledrv_llseek,
	.read = simpledrv_read,
	.write = simpledrv_write,
	.ioctl = simpledrv_ioctl,
	.open = simpledrv_open,
	.release = simpledrv_release,
};


/*驱动接口具体实现*/
int simpledrv_open(struct inode *inode, struct file *filp)
{
	filp->private_data = devp;
	return 0;
}

int simpledrv_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t simpledrv_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{
	printk(KERN_ALERT "read\n");

	/*一般主要工作是：
	 *完成数据中内核空间到用户空间之间的复制,参数:目标地址(用户空间)，源地址（内核空间），字节数.
	 *返回不能被复制的字节数，如果成功返回0*/
	/*
	if(copy_to_user(..., ...,...))
	{
		printk(KERN_ALERT "some error2\n");
		ret = -EFAULT;
	}
	 *ppos += count;
	 ret = count;
	 */
	return 0;
}

static ssize_t simpledrv_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
	struct simpledrv_dev *dev;
	dev = filp->private_data;
	printk(KERN_ALERT "write!\n");

	/*一般主要工作是：
	 *完成数据用户空间到内核空间之间的复制,参数:目标地址(用户空间)，源地址（内核空间），字节数.
	 *返回不能被复制的字节数，如果成功返回0*/
	/*
	if(copy_from_user(..., ..., ...))
	{
		ret = -EFAULT;
	}
	*ppos += count;
	ret = count;
	*/
	return 0;
}

static loff_t simpledrv_llseek(struct file *filp, loff_t offset, int orig)
{
	printk(KERN_ALERT "llseek!\n");
	return 0;
}

static int simpledrv_ioctl(struct inode *inodep, struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct simpledrv_dev *dev;
	dev = filp->private_data;
	printk(KERN_ALERT "ioctl!\n");

	/*主要内容：*/
	/*
	switch(cmd)
	{
		case ...:
		case ...:
		break;
		default:
		return -EINVAL;
	}
	*/
	return 0;
}

/*驱动加载函数*/
int simpledrv_init(void)
{
	int result;
	int err;
	dev_t devno = MKDEV(simpledrv_major,0);/*devno可以任意设置这里只是一个初始化*/

/*!!!!!动态申请设备号*/
	result = alloc_chrdev_region(&devno, 0,1, "simpledrv_std");
	simpledrv_major = MAJOR(devno);

	if(result < 0)
	{
		printk(KERN_ALERT "Error register simpledrv result:%d\n", result);
		return result;
	}

/*!!!分配设备驱动结构指针的内存*/
	devp = kmalloc(sizeof(struct simpledrv_dev),GFP_KERNEL);
	if(!devp)
	{
		result = -ENOMEM;
		unregister_chrdev_region(devno,1);
		return 0;
	}
	memset(devp, 0, sizeof(struct simpledrv_dev));

/*!!!添加设备*/
	cdev_init(&devp->cdev, &simpledrv_fops);
	devp->cdev.owner = THIS_MODULE;
	err = cdev_add(&devp->cdev, devno, 1);
	if(err)
	{
		printk(KERN_ALERT "Error %d adding simpledrv", err);
	}
	return 0;
}

/*驱动卸载函数*/
void simpledrv_exit(void)
{
	cdev_del(&devp->cdev);

	/*+++这里释放设备结构体内存*/
	kfree(devp);
	/*注销设备号，在simpledrv_init中注册的设备号应该一致*/
	/*第一个参数是设备号，第二参数是次设备的数目*/
	unregister_chrdev_region(MKDEV(simpledrv_major, 0), 1);
}

module_init(simpledrv_init);
module_exit(simpledrv_exit);
