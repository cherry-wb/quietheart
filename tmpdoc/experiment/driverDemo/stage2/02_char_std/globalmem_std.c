/*一、功能：本例子使用一个相对比较标准的方法定义了一种字符设备，
 *这个设备是一个全局内存字符设备，其功能是：
 *一个程序向该设备对应的设备文件中写入数据，另一个程序可以从这个设备文件中读取数据。
 *另外这个设备驱动支持清除设备文件中所有的数据为空。
 *当前相对于前面的例子(char_simple)，标准的地方是：
 *1）没有直接定义全局设备对象，而是把设备对象在初始化函数中动态初始化，在文件私有数据中指向该地址
 *2)设备号码不用静态分配而直接用动态分配了，因为静态分配想要标准的还要查询一个devices.txt文件
 *3)ioctl命令码的生成方式比较标准了
 *在对应的地方，都有说明的。另外，把模块的init和exit函数放在了最后。
 *在下一个例子中会给出一个相对典型的方法。
 *二、使用说明：
 *1)编译
 *$make
 *2)插入模块
 *insmod globalmem_std.ko
 *可以通过"cat /proc/devices"得知设备的主从号码
 *3)创建设备文件
 *#mknod mytest c <主设备号> 0
 *4)使用
 *写入数据：echo hello >mytest
 *读取数据：cat mytest
 *ioctl：使用testDemo中的代码进行测试。
 *5)卸载模块
 *rmmod globalmem_std

 *注意:关键的地方我都用"+++"来标记了.
 *问题：为什么lsmod有输出，cat /proc/devices没有？并且无法创建设备文件?
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


/*全局内存大小4k*/
#define GLOBALMEM_SIZE 0x1000
/***清零全局内存*/
//#define MEM_CLEAR 0x1
/*+++见后面ioctl函数前的注释，这里有待研究我也不太懂究竟怎么确定这个魔术数,就随便选了一个*/
#define GLOBALMEM_MAGIC 'D'
#define MEM_CLEAR _IO(GLOBALMEM_MAGIC,0)
/***预设的主设备号*/
/*在kernel源码中的Documentation中的devices.txt中预设了约260个,所以为了避免冲突这里设的大一些*/
/*这里既然已经动态分配了，实际没有意义了，只是为了给一个变量一个初始值*/
#define GLOBALMEM_MAJOR 1025

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Quiet Heart");
MODULE_DESCRIPTION("This is a simple global memory module.");
MODULE_ALIAS("global memory module");

/*globalmem设备结构体，其中struct cdev是通用的成员，其它的是自定义与设备相关的成员*/
struct globalmem_dev
{
	/*字符设备结构体*/
	/*在"linux/cdev.h"中有定义*/
	/*其关键成员是:
	dev_t dev;代表当前设备号,32位，高12位主设备号，低20位次设备号,参考内核源码Document中devices.txt。
	struct file_operations ops;代表设备操作函数
	struct module *owner;代表设备驱动对应的当前模块
	*/
	struct cdev cdev;
	/*全局内存*/
	unsigned char mem[GLOBALMEM_SIZE];
};

/*声明自定义函数*/
static void globalmem_setup_cdev(struct globalmem_dev *dev,int index);
int globalmem_open(struct inode *inode, struct file *filp);
int globalmem_release(struct inode *inode, struct file *filp);
static ssize_t globalmem_read(struct file *filp, char __user *buf, 
							size_t count, loff_t *ppos);
static ssize_t globalmem_write(struct file *filp, const char __user *buf, 
							size_t count, loff_t *ppos);
static loff_t globalmem_llseek(struct file *filp, loff_t offset, int orig);
static int globalmem_ioctl(struct inode *inodep, struct file *filp, 
					unsigned int cmd, unsigned long arg);

/*声明结构和变量*/
static int globalmem_major = GLOBALMEM_MAJOR;
/*+++这里不用全局变量，而用一个设备结构体指针了*/
struct globalmem_dev *devp;

/*与字符设备结构体操作相关的函数指针结构体*/
/*相应的操作在指定之后，对与用户空间就相当于系统调用的实现了*/
/*在"linux/fs.h"中有定义*/
static const struct file_operations globalmem_fops = 
{
	/*管理此设备的模块指针，例如使用try_module_get/module_put等接口
	 *对owner操作来管理此设备owner模块的使用计数,可确保设备使用时管理设备的模块不被卸载
	 *一般驱动工程师很少亲自调用try_module_get和module_put,而只写具体设备的管理模块(驱动)*/
	/*当insmod的时候会把当前的模块传递给struct module,而THIS_MODULE类似current代表当前模块*/
	/*在"linux/module.h中有定义"*/
	.owner = THIS_MODULE,

	/*自定义的驱动接口，在用户空间以系统调用的形式被调用*/
	.llseek = globalmem_llseek,
	.read = globalmem_read,
	.write = globalmem_write,
	.ioctl = globalmem_ioctl,
	.open = globalmem_open,
	.release = globalmem_release,
};


static void globalmem_setup_cdev(struct globalmem_dev *dev,int index)
{
	int err, devno = MKDEV(globalmem_major, index);

	/*注册完设备号之后，初始化自定义的设备结构成员
	 *主要是：设备号，管理模块指针，设备文件（驱动）支持的操作函数结构体*/
	/*在"linux/cdev.h"中声明*/
	cdev_init(&dev->cdev, &globalmem_fops);
	dev->cdev.owner = THIS_MODULE;
	//dev->cdev.ops = &globalmem_fops;//多余?

	/*添加初始化好的自定义设备，需要在注册完设备号之后才能调用*/
	/*第一个参数是对应的字符设备结构体，第二个是设备号，第三个是次设备数目*/
	/*在"linux/cdev.h"中声明*/
	err = cdev_add(&dev->cdev, devno, 1);
	if(err)
	{
		printk(KERN_ALERT "Error %d adding globalmem", err);
	}
}

/*打开设备函数*/
int globalmem_open(struct inode *inode, struct file *filp)
{
	/*+++这里是获得设备驱动的结构变量，因为这个变量不是全局的了，所以通过open来获取它*/
	filp->private_data = devp;
	return 0;
}

/*关闭函数,文件释放*/
int globalmem_release(struct inode *inode, struct file *filp)
{
	return 0;
}

/*自定义设备驱动的读函数*/
/*参数分别是：设备文件，读取的数据存放的目标用户空间缓存，要读取的字节数，读取的起始偏移位置*/
/*返回值：读取的数目*/
/*其中的loff_t类型在"linux/types.h"中有定义*/
static ssize_t globalmem_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{
	printk(KERN_ALERT "read\n");
	/*+++获取设备结构体指针*/
	struct globalmem_dev *dev = filp->private_data;

	/*将设备数据读取出来（到用户空间），设备数据当然存放在自定义设备结构体的数组中*/
	unsigned long p = *ppos;
	int ret = 0;
	if(p > GLOBALMEM_SIZE)
	{
		/*这里如果是"p>="在每次读的时候都会进入，不知道为什么，写入之后数据正确读出了之后也会进到这里*/
		printk(KERN_ALERT "some error1\n");
		return count ? -ENXIO:0;
	}
	if(count > GLOBALMEM_SIZE - p)
	{
		count = GLOBALMEM_SIZE - p;
	}

	/*完成数据中内核空间到用户空间之间的复制,参数:目标地址(用户空间)，源地址（内核空间），字节数.
	 *返回不能被复制的字节数，如果成功返回0*/
	/*应该在"arch/x86/include/asm/uaccess_64.h"有一个声明不知道是不是，
	 *内核源码的"arch/x86/lib/usercopy_32.c"定义它，并导出到内核空间(在/proc/kallsyms)*/
	if(copy_to_user(buf, (void*)(dev->mem + p), count))
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

/*自定义设备驱动的写函数*/
/*参数分别是：设备文件，写的数据存放的用户空间缓存，要写的字节数，写的起始偏移位置*/
/*返回值：写了的数目*/
/*其中的loff_t类型在"linux/types.h"中有定义*/
static ssize_t globalmem_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
	printk(KERN_ALERT "write!\n");
	/*+++获取设备结构体指针*/
	struct globalmem_dev *dev = filp->private_data;

	/*将设备数据写（到设备驱动缓存中），源数据当然存放在用户空间程序中*/
	/*在c89/90 标准里，一个函数里变量的定义要放在代码段前面，所以这里会有警告不符标准*/
	/*把上面的printk注释掉就没有那个警告了*/
	unsigned long p = *ppos;
	int ret = 0;
	if(p > GLOBALMEM_SIZE)
	{
		return count ? -ENXIO:0;
	}
	if(count > GLOBALMEM_SIZE -p)
	{
		count = GLOBALMEM_SIZE - p;
	}
	/*完成数据用户空间到内核空间之间的复制,参数:目标地址(用户空间)，源地址（内核空间），字节数.
	 *返回不能被复制的字节数，如果成功返回0*/
	/*应该在"arch/x86/include/asm/uaccess_64.h"有一个声明不知道是不是，
	 *内核源码的"arch/x86/lib/usercopy_32.c"定义它，并导出到内核空间(在/proc/kallsyms)*/
	if(copy_from_user(dev->mem + p, buf, count))
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

/*文件指针定位函数,移动当前文件的指针到指定的位置，返回这个位置
具体参见系统调用lseek.这里只支持从文件开头和当前位置的偏移*/
static loff_t globalmem_llseek(struct file *filp, loff_t offset, int orig)
{
	printk(KERN_ALERT "llseek!\n");
	loff_t ret;
	switch(orig)
	{
		/*case 0:从文件开头偏移*/
		case SEEK_SET:
			if(offset < 0)
			{
				ret = -EINVAL;
				break;
			}
			if((unsigned int)offset > GLOBALMEM_SIZE)
			{
				ret = -EINVAL;
				break;
			}
			filp->f_pos = (unsigned int)offset;
			ret = filp->f_pos;
			break;
		/*case 1:从当前位置偏移*/
		case SEEK_CUR:
			if((filp->f_pos+offset) > GLOBALMEM_SIZE)
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
		case SEEK_END:/*从当前位置偏移*/
			if(offset > 0)
			{
				ret = -EINVAL;
				break;
			}
			if(offset < -GLOBALMEM_SIZE)
			{
				ret = -EINVAL;
				break;
			}
			filp->f_pos = offset+GLOBALMEM_SIZE;
			ret = filp->f_pos;
			break;
		default:
			ret = -EINVAL;
	}
	return ret;
}

/*设备驱动的ioctrl函数，这个函数进行除了一般文件读写等之外的，和具体设备相关的自定义操作*/
/*参数：第一个，第二个分别是文件相关，很容易明白,关键是第三个参数
 *第三个参数：代表特定功能的命令码
 *第四个参数：相应命令码的参数(如果命令码需要参数的话)*/
/*对于这个函数的地三个参数命令吗，本例子直接指定了一个自定义的数目，实际上不标准，标准方法是：
 *命令码的32位分别是：设备类型(8bit),序列号(8bit)方向(2bit)数据尺寸(13/14bit)
 *其中，设备类型是一个幻数在0-0xff之间，内核源码的Documentation/ioctl/ioctl-number.txt给出了推荐
 *序列号也8位，方向四种可能：无，读，写，读／写*/
/*关于生成ioctl命令标准方法，参见下一个例子，一般是使用设备幻数和四个宏辅助生成命令码：
 *_IO,_IOR,_IOW,_IOWR,这四个宏的定义在"arch/x86/include/asm/ioctl.h"包含的
 *"/usr/include/asm-generic/ioctl.h"中，
 *根据定义，几个宏根据传入的type(设备类型),nr(序列号),size(数据大小)及宏名隐含的方向信息生成命令码，
 *使用例如：
 *#define GLOBALMEM_MAGIC ...
 *#define MEM_CLEAR _IO(GLOBALMEM_MAGIC,0)*/
static int globalmem_ioctl(struct inode *inodep, struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk(KERN_ALERT "ioctl!\n");

	/*+++获取设备结构体指针*/
	struct globalmem_dev *dev = filp->private_data;

	switch(cmd)
	{
		/*根据传入的命令码，跳转到不同的分支*/
		case MEM_CLEAR:
		memset(dev->mem,0,GLOBALMEM_SIZE);
		printk(KERN_ALERT "globalmem is set to zero\n");
		break;
		default:
		return -EINVAL;
	}
	return 0;
}

/*驱动加载函数*/
int globalmem_init(void)
{
	int result;
	/*根据指定的整数创建设备号,两个参数分别表示主设备号和次设备号*/
	/*dev_t在"linux/types.h中定义；MKDEV在"linux/cdev.h"中包含的kdev_t.h中定义*/
	/*由于不采用静态分配了，所以这里的作用不大，只是为了随意弄一个初始值*/
	dev_t devno = MKDEV(globalmem_major,0);

#if  0
	/*静态分配设备号参考*/
	if(globalmem_major)
	{
		/*如果指定设备号，根据设备号静态申请设备驱动区域(注册设备号)*/
		/*第一个参数是指定的设备号，第二个参数是要注册的设备数目，第三个是驱动名称/proc/devices*/
		/*这个函数在"linux/fs.h"声明*/
		/*这个函数在内核源代码的"fs/chardev.c"中定义,并用EXPORT_SYMBOL导出到/proc/kallsyms*/
		/*关于分配设备号相关建议，应该阅读内核源码中"Documentation/devices.txt"*/
		/*register_chrdev_region是register_chrdev()的升级版本,多了向内核注册添加cdev设备的步骤*/
		result = register_chrdev_region(devno, 1, "globalmem_std");
	}
	else
	{
#endif
		/*没有指定设备号的动态申请*/
		/*参数第一个是返回的设备号，第二个是起始次设备号一般是0，第三个是设备数目，第四个是驱动名*/
		/*定义位置和静态分配一样*/
		result = alloc_chrdev_region(&devno, 0,1, "globalmem_std");

		/*静态分配设备号参考*/
		/*根据设备号获取对应主设备号,在"linux/kdev_t.h"定义*/
		globalmem_major = MAJOR(devno);
#if  0
	}
#endif

	if(result < 0)
	{
		printk(KERN_ALERT "Error register globalmem result:%d\n", result);
		return result;
	}

	/*+++在这里分配设备驱动结构指针的内存*/
	devp = kmalloc(sizeof(struct globalmem_dev),GFP_KERNEL);
	if(!devp)
	{
		result = -ENOMEM;
		goto fail_malloc;
	}
	memset(devp, 0, sizeof(struct globalmem_dev));

	globalmem_setup_cdev(devp, 0);
	printk(KERN_ALERT "Hello,globalmem driver inserted,major number is %d\n", globalmem_major);

	fail_malloc:unregister_chrdev_region(devno,1);
	return 0;
}

/*驱动卸载函数*/
void globalmem_exit(void)
{
	cdev_del(&devp->cdev);

	/*+++这里释放设备结构体内存*/
	kfree(devp);
	/*注销设备号，在globalmem_init中注册的设备号应该一致*/
	/*第一个参数是设备号，第二参数是次设备的数目*/
	unregister_chrdev_region(MKDEV(globalmem_major, 0), 1);
}

module_init(globalmem_init);
module_exit(globalmem_exit);
