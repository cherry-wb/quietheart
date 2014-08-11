/*一、功能：
 *测试自旋锁
 *这里，在open中使用了最简单的自旋锁。
 *添加自旋锁之后，对临界资源xxx_count的访问就只限一个进程
 *如果没有spinlock/spin_unlock那么，可能多个进程同时访问xxx_count.
 *例如这个例子中，a访问xxx_count确认是否进入if(xxx_count)，确认是不进入，在修改xxx_count前被b打断；
 *然后b也访问此时a还没修改的xxx_count,所以b也不进入，而这里本意是b要进入if分支的。
 *关于spinlock文档，参考内核源代码：Documentation/spinlocks.txt
 *在spinlock持有期间，进程一直占用cpu并不切换出去，这一点和信号不同。
	

 *二、一般驱动简易使用说明：
 *1)编译
 *$make
 *2)插入模块
 *insmod simplespinlock.ko
 *可以通过"cat /proc/devices"得知设备的主从号码
 *3)创建设备文件
 *#mknod mytest c <主设备号> 0
 *4)卸载模块
 *rmmod simplespinlock

 *查看驱动信息：
 $modinfo simplespinlock.ko
 *
 *问题：
 *不知道为什么，使用echo good>/dev/mytest会循环打印write没有结束。
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

/*+++使用自旋锁，必须包含这个头文件*/
#include <linux/spinlock.h>


#define simpledrv_SIZE 0x1000
#define simpledrv_MAJOR 1025

/*module info*/
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Quiet Heart");
MODULE_DESCRIPTION("This is a simple spinlock module.");
MODULE_ALIAS("spinlock module");

/*simpledrv*/
struct simpledrv_dev
{
	struct cdev cdev;
};

/*function*/
int simpledrv_open(struct inode *inode, struct file *filp);
int simpledrv_release(struct inode *inode, struct file *filp);
static ssize_t simpledrv_read(struct file *filp, char __user *buf, 
							size_t count, loff_t *ppos);
static ssize_t simpledrv_write(struct file *filp, const char __user *buf, 
							size_t count, loff_t *ppos);
static loff_t simpledrv_llseek(struct file *filp, loff_t offset, int orig);
static int simpledrv_ioctl(struct inode *inodep, struct file *filp, 
					unsigned int cmd, unsigned long arg);

/*variable*/
static int simpledrv_major = simpledrv_MAJOR;
struct simpledrv_dev *devp;

int xxx_count = 0;/*record the count of open*/
spinlock_t count_lock;

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


/*impl*/
int simpledrv_open(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "device open!\n");

	/*+++加锁，访问临界资源，释放锁*/
	spin_lock(&count_lock);
	if(xxx_count)
	{
		spin_unlock(&count_lock);
		printk(KERN_ALERT "device is busy!\n");
		return - EBUSY;
	}
	++xxx_count;
	spin_unlock(&count_lock);
	filp->private_data = devp;
	return 0;
}

int simpledrv_release(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "device close!\n");

	/*+++加锁，访问临界资源，释放锁*/
	spin_lock(&count_lock);
	--xxx_count;
	spin_unlock(&count_lock);
	return 0;
}

static ssize_t simpledrv_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{
	printk(KERN_ALERT "read\n");

	return 1;
}

static ssize_t simpledrv_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
	struct simpledrv_dev *dev;
	dev = filp->private_data;
	printk(KERN_ALERT "write!\n");

	return 1;
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

	return 0;
}

int simpledrv_init(void)
{
	int result;
	int err;
	dev_t devno = MKDEV(simpledrv_major,0);

	result = alloc_chrdev_region(&devno, 0,1, "simplespinlock");
	simpledrv_major = MAJOR(devno);
	if(result < 0)
	{
		printk(KERN_ALERT "Error register simpledrv result:%d\n", result);
		return result;
	}

	devp = kmalloc(sizeof(struct simpledrv_dev),GFP_KERNEL);
	if(!devp)
	{
		result = -ENOMEM;
		unregister_chrdev_region(devno,1);
		return 0;
	}
	memset(devp, 0, sizeof(struct simpledrv_dev));

	cdev_init(&devp->cdev, &simpledrv_fops);
	devp->cdev.owner = THIS_MODULE;
	err = cdev_add(&devp->cdev, devno, 1);
	if(err)
	{
		printk(KERN_ALERT "Error %d adding simpledrv", err);
	}

	/*other initialize*/
	/*+++初始化自旋锁*/
	spin_lock_init(&count_lock);
	printk(KERN_ALERT "driver initialize!\n");
	return 0;
}

void simpledrv_exit(void)
{
	cdev_del(&devp->cdev);

	kfree(devp);
	unregister_chrdev_region(MKDEV(simpledrv_major, 0), 1);
	printk(KERN_ALERT "driver exit!\n");
}

module_init(simpledrv_init);
module_exit(simpledrv_exit);
