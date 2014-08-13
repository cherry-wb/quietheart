/*程序功能：
 * 建立一个只读的字符设备，
 * 当读取时输出你从这个文件中读取过的次数(实际是读取同样主设备号的文件次数).
 * 当你向设备写的时候输出提示，提示不支持写操作。
 * */
/*程序的使用方法：
 *1）加载这个模块：
 * $insmod chardev.ko
 * 这将输出一些信息，其中一条说明这个模块支持的设备文件的主设备号，假设是252
 *2）根据前面的设备号，建立设备文件：
 * $mknod /dev/mychar_252_1 c 252 1
 * $mknod /dev/mychar_252_2 c 252 2
 *命令建立了两个设备文件mychar_252_*，这里c代表字符，之后两个是主从设备号.
 *内核实际并不关注从设备号，只要主设备号对了就好，主设备号指明要用的驱动。
 *注意设备文件要建立在/dev/下，若不建在这下面，无法操作。
 后来放到root的家下面用root可以执行了，估计是权限问题。
 *3) 操作文件：
 *$cat /dev/mychar_252_2
 *$cat /dev/mychar_252_1
 *这两个命令用于读取。
 *$echo test >/dev/mychar_252_1
 *这个命令用于写入。 
 * */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
/* for put_user */
#include <asm/uaccess.h>	

/*一些声明，这些应该放到头文件中去*/
int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0

/*设备名称，会在/proc/devices中出现*/
#define DEVICE_NAME "chardev"

/*来自这个设备的最大消息长度*/
#define BUF_LEN 80

/*
 *以静态的方式来定义全局变量,这样变量具有文件域的范围
 * */
/*主设备号*/
static int Major;		
/*设备的打开状态，防止多重访问*/
static int Device_Open = 0;	  
/*访问设备时设备返回的消息*/
static char msg[BUF_LEN];
static char *msg_Ptr;

/*这个结构的定义在/usr/src/linux-headers-2.6.24-19-generic/include/linux/fs.h
 * 定义了设备的相关操作，不用全部都实现。
 * 这里确定特定的设备操作使用那些函数来完成*/
static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

/******函数的实现******/

int init_module(void)
{
	/*注册设备，起参数分别为：
	 * 第一个参数:主设备号，为0表示动态分配一个
	 * 第二个参数：设备名称，将在/proc/devices中列出
	 * 第三个参数：与该设备相关的操作
	 * 返回值应该是主设备号*/
	Major = register_chrdev(0, DEVICE_NAME, &fops);

	if (Major < 0) {
		printk("Registering the character device failed with %d\n",
				Major);
		return Major;
	}

	/*没有<1>的在我的机器上面都没有打印出来。*/
	printk("<1>I was assigned major number %d.  To talk to\n", Major);
	printk("<1>the driver, create a dev file with\n");
	printk("<1>'mknod /dev/hello c %d 0'.\n", Major);
	printk("<1>Try various minor numbers.  Try to cat and echo to\n");
	printk("<1>the device file.\n");
	printk("<1>Remove the device file and module when done.\n");

	return 0;
}

void cleanup_module(void)
{
	/* 
	 * 将指定的设备“卸载”
	 **/
	printk("<1>bye bye!\n");
	unregister_chrdev(Major, DEVICE_NAME);
	/*以前的有返回值，现在没有了。
	int ret = unregister_chrdev(Major, DEVICE_NAME);
	if (ret < 0)
		printk("Error in unregister_chrdev: %d\n", ret);*/
}


/*这个函数当进程打开设备文件的时候调用，例如cat /dev/mycharfile
 **/
static int device_open(struct inode *inode, struct file *file)
{
	static int counter = 0;
	if (Device_Open)
		return -EBUSY;
	Device_Open++;
	sprintf(msg, "I already told you %d times Hello world!\n", counter++);
	msg_Ptr = msg;

	/*这个宏用来使设备使用计数器增1,计数器跟踪这有多少进程正在使用该模块*/
	try_module_get(THIS_MODULE);

	return SUCCESS;
}

/*这个函数当进程关闭设备文件的时候调用。*/
static int device_release(struct inode *inode, struct file *file)
{
	Device_Open--;

	/*这个宏用来使设备使用计数器减1，否则一旦你打开设备文件，就无法摆脱这模块了*/
	module_put(THIS_MODULE);

	return 0;
}

/*这个函数当有一个进程打开了本设备文件，想要读取这个文件的时候调用
 * 其参数如下：
 * filp是文件指针，见/usr/src/linux-headers-`uname -r`/include/linux/fs.h
 * buffer:将要读取的数据存放在这个buffer数组里,它是一个用户空间的字符数组
 * length:buffer的长度
 * offset*/
static ssize_t device_read(struct file *filp,
		char *buffer,
		size_t length,
		loff_t * offset)
{

	 /*存放保存到buffer数组的字节数（读取的字节数）
	 */
	int bytes_read = 0;

	/*msg_Ptr里面含有设备将要被读取的信息,如果到达消息结尾返回0表示文件结束*/
	if (*msg_Ptr == 0)
		return 0;

	/*循环将把数据复制（读取）到buffer中去*/
	while (length && *msg_Ptr)
	{/*如果长度没有超过buffer长度并且消息还没有读取完，则继续循环*/

		/*因为buffer是在用户数据空间段的数组而不是内核空间段的数据，
		 * 所以直接用*赋值是不行的，
		 * 我们需要使用put_user函数把数据从内核空间拷贝到用户空间*/
		put_user(*(msg_Ptr++), buffer++);

		length--;
		bytes_read++;
	}

	/*返回已经读取的字节数目*/
	return bytes_read;
}

/*这个函数在当有进程写这个设备文件的时候调用，例如echo "hi"> /dev/hello*/
static ssize_t
device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	printk("<1>Sorry, this operation isn't supported.\n");
	return -EINVAL;
}
