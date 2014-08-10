/*程序功能：这个是模块实现的相关代码，包括读写以及ioctl操作*/
/*创建一个输入/输出字符设备*/
/*一般都是通过读写设备文件操作和设备进行通信，
 * 但有的设备需要别的操作所以ioctl,它包含了更多的操作*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include "chardev.h"
#define SUCCESS 0
//#define DEVICE_NAME "char_dev"
#define BUF_LEN 80

/*确定设备现在是否已经打开，用来保护访问同一个设备*/
static int Device_Open = 0;

/*当被请求时，设备提供供的消息*/
static char Message[BUF_LEN];

/*进程读取的消息的进度，当消息比我们device_read填充的缓冲大小大的时候很有用。*/
static char *Message_Ptr;

/*当一个进程打开这个设备文件的时候会调用这个函数*/
static int device_open(struct inode *inode, struct file *file)
{
#ifdef DEBUG
	printk("<1>device_open(%p)\n", file);
#endif

	/*控制不能同一个时间和两个进程进行对话,不能两个进程同时打开这个设备文件*/
	if (Device_Open)
		return -EBUSY;

	Device_Open++;

	/*初始话消息指针，指向消息*/
	Message_Ptr = Message;
	/*增加引用计数*/
	try_module_get(THIS_MODULE);
	return SUCCESS;
}

/*释放／关闭设备文件时候调用这个函数*/
static int device_release(struct inode *inode, struct file *file)
{
#ifdef DEBUG
	printk("<1>device_release(%p,%p)\n", inode, file);
#endif

	/*这样以便其他进程打开设备文件*/
	Device_Open--;
	/*减少引用计数*/
	module_put(THIS_MODULE);
	return SUCCESS;
}

/*这个函数在一个进程读取打开的设备文件的时候被调用*/
/*函数的参数意义如下：
 * file：可以参见include/linux/fs.h
 * buffer:读取数据将要填充到这个buffer里面
 * length:buffer的长度
 *
 * */
static ssize_t device_read(struct file *file,
		char __user * buffer,
		size_t length,
		loff_t * offset)
{
	/*已经写入到buffer的字节数目*/
	int bytes_read = 0;

#ifdef DEBUG
	printk("<1>device_read(%p,%p,%d)\n", file, buffer, length);
#endif

	/*如果到达消息结尾，返回0，表示文件的结尾*/
	if (*Message_Ptr == 0)
		return 0;

	/*这里把数据填充到buffer中去*/
	while (length && *Message_Ptr)
	{

		/*把数据从内核空间拷贝到用户空间（buffer）中，这里不能用赋值*/
		put_user(*(Message_Ptr++), buffer++);
		length--;
		bytes_read++;
	}

#ifdef DEBUG
	printk("<1>Read %d bytes, %d left\n", bytes_read, length);
#endif

	/*返回读取的字节数目*/
	return bytes_read;
}

/*这个函数在有其他人向我们的设备文件中写入数据的时候被调用
 * 参数和前面的device_read类似，
 * 不过这里的buffer是待写的数据缓存，而不是接收读取的数据缓存了*/
static ssize_t
device_write(struct file *file,
		const char __user * buffer, size_t length, loff_t * offset)
{
	int i;

#ifdef DEBUG
	printk("<1>device_write(%p,%s,%d)", file, buffer, length);
#endif

	for (i = 0; i < length && i < BUF_LEN; i++)
		get_user(Message[i], buffer + i);

	Message_Ptr = Message;

	/*返回写入的字节数目*/
	return i;
}

/*这个函数在当一个进程尝试给我们的设备文件发送ioctl请求的时候会被调用。
 * 这个函数操作设备，它“集中”包含了读／写以及其他的各种自定义操作.
 * 函数的参数如下：（其中后两个参数是最重要的ioctl参数）
 * inode:设备节点结构,可以查看include/linux/fs.h
 * file:设备文件结构
 * ioctl_num:设备控制号(这里标志控制的类型，其中包括读和写，一般应该也这么做)
 * ioctl_param:传给ioctl相应控制操作的参数
 *
 * 如果ioctl是写或读/写（意思是输出会返回给调用的进程），
 * 那么ioctl调用会返回这个函数的输出。
 * */
int device_ioctl(struct inode *inode,
		struct file *file,
		unsigned int ioctl_num,
		unsigned long ioctl_param)
{
	int i;
	char *temp;
	char ch;

	/*根据ioctl调用时ioctl_num指定的各种动作情况*/
	switch (ioctl_num)
	{
		case IOCTL_SET_MSG:
			/*这个动作表示将要向file中写入被当成字符串的ioctl_param的内容*/

			/*用户空间的消息指针，设置为设备消息。这里获得进程传递给ioctl的参数*/
			temp = (char *)ioctl_param;

			/*获得长度*/
			get_user(ch, temp);
			for (i = 0; ch && i < BUF_LEN; i++, temp++)
				get_user(ch, temp);

			device_write(file, (char *)ioctl_param, i, 0);
			break;

		case IOCTL_GET_MSG:
			/*这个操作表示将要向file中读取内容到被当成字符串的ioctl_param*/

			/*获得当前的消息给调用的进程，消息会填充到ioctl_param这个指针中*/
			/*注意这里的缓存大限就用99了，实际情况见ioctl.c中的解释*/
			i = device_read(file, (char *)ioctl_param, 99, 0);

			/*只是增加一个字符串结束符号*/
			put_user('\0', (char *)ioctl_param + i);
			break;

		case IOCTL_GET_NTH_BYTE:
			/*这个操作表示将要返回Message消息中第ioctl_param个字符*/

			/*这个ioctl操作既能输入(ioctl_param)也能输出(这个函数的返回值)
			 * 这里利用用户传进来的参数号码ioctl_param来返回（得到）
			 * 第ioctl_param字节的消息（字符）的位置。*/
			return Message[ioctl_param];
			break;
	}

	return SUCCESS;
}

/*模块声明相关*/

/*这个结构包含了操作设备的时候调用的函数。
 * 因为这个结构的一个指针保存在设备表中，它不能够在init_module中被定位
 * NULL用于没有执行的函数*/
struct file_operations Fops =
{
	.read = device_read,
	.write = device_write,
	.ioctl = device_ioctl,
	.open = device_open,

	/* a.k.a. close */
	.release = device_release,	
};

/*初始化模块，注册字符设备*/
int init_module()
{
	printk("<1>hi,init_module!\n");
	int ret_val;

	/*注册字符设备(至少try),这里可不是动态的了啊??????*/
	ret_val = register_chrdev(MAJOR_NUM, DEVICE_FILE_NAME, &Fops);

	if (ret_val < 0)
	{
		printk("<1>%s failed with %d\n",
				"Sorry, registering the character device ", ret_val);
		return ret_val;
	}

	printk("<1>%s The major device number is %d.\n",
			"Registeration is a success", MAJOR_NUM);
	printk("<1>If you want to talk to the device driver,\n");
	printk("<1>you'll have to create a device file. \n");
	printk("<1>We suggest you use:\n");
	printk("<1>mknod %s c %d 0\n", DEVICE_FILE_NAME, MAJOR_NUM);
	printk("<1>The device file name is important, because\n");
	printk("<1>the ioctl program assumes that's the\n");
	printk("<1>file you'll use.\n");

	return 0;
}

/*清理，反注册/proc中的特定文件*/
void cleanup_module()
{
	printk("<1>bye bye,cleanup_module!\n");
	/*这里会反注册设备*/
	unregister_chrdev(MAJOR_NUM, DEVICE_FILE_NAME);

	/*在include/linux/fs.h中可以知道，这个函数的返回值是void,所以下面的方法错*/
	/*int ret;
	ret = unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
	if (ret < 0)
		printk("Error in module_unregister_chrdev: %d\n", ret);
	*/
}
