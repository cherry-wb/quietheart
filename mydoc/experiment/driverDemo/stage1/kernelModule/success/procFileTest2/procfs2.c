/*程序功能：在/proc中创建一个文件,允许读写*/

/*问题：编译有些警告，说变量的声明和编码混合了不知道怎么回事。*/
/*kernel*/
#include <linux/kernel.h>
/*module*/
#include <linux/module.h>
/*procfs*/
#include <linux/proc_fs.h>
/*get_user and put_user*/
#include <asm/uaccess.h>
/*for the 'current'*/
#include <linux/sched.h>

/*for geteuid*/
//#include<unistd.h>

/*这里我们保持上次接收到的消息,证明我们能够处理我们的输入*/
#define MESSAGE_LENGTH 80
static char Message[MESSAGE_LENGTH];
static struct proc_dir_entry *Our_Proc_File;

#define PROC_ENTRY_FILENAME "rw_test"

/*函数功能：相当于读取数据到用户空间
 * 关于参数：
 * filp:可以查看/usr/src/linux-headers-2.6.24-19-generic/include/linux
 * buffer:用于填充数据的buffer,读取的数据最后就应该存放到这里面
 * length:buffer的长度
 * */
static ssize_t module_output(struct file *filp,	
		char *buffer,
		size_t length,
		loff_t * offset)
{
	static int finished = 0;
	/*读取的字节数目*/
	int i;
	char message[MESSAGE_LENGTH + 30];

	/*返回零表示文件的结尾,否则进程会继续从我们这里读取从而陷入死循环*/
	if (finished)
	{
		finished = 0;
		return 0;
	}

	/*使用put_user把数据从内核内存空间拷贝到进程内存空间
	 * 顺便指出：get_user进行相反的操作。
	 * */
	sprintf(message, "Last input:%s", Message);
	for (i = 0; i < length && message[i]; i++)
		put_user(message[i], buffer + i);

	/*注意，这里我们假设消息的大小小于len，如果超过了，那么就会截取接收。
	 * 在实际中，如果消息的大小小于len,我们会返回len,并且在第二此调用的时候
	 * 开始由len+1开始填充消息字节*/
	finished = 1;

	/*返回读取的字节数目*/
	return i;
}

/*写文件的函数,将要写入的数据（在buffer里面）存放到Message里面。*/
static ssize_t
module_input(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	int i;

	/*把输入存放在Message（全局）数组中，这样module_output以后能够使用它*/
	for (i = 0; i < MESSAGE_LENGTH - 1 && i < len; i++)
		get_user(Message[i], buff + i);

	Message[i] = '\0';
	return i;
}

/*这个函数用来决定是否允许一个指定的操作。
 * 如果允许那么返回0，否则返回非零（并且根据数值决定为什么不被允许）
 * 操作包含如下的值：
 * 0 -执行（在我们的例子里，执行这个文件没有什么意义）
 * 2 -写入（写入到内核的模块当中）
 * 4 -读取（从内核模块读取数据）
 *
 * 这里的函数是实际执行文件权限检查的。ls -l返回的权限仅供参考，并且可在这覆盖
 * */

static int module_permission(struct inode *inode, int op, struct nameidata *foo)
{
	/*我们允许每一个人从我们的模块中读取，但是只有root用户才能够写它*/
	/*倒是在include/asm-x86/current.h中看到了current是一宏定义调用get_current*/
	/*就是task_struct,定义在linux/sched.h*/
	/*100||010&&euid==0,表示如果是所有用户读，或者是超级用户写。*/ 
	if(op == 4 || (op == 2 && current->euid == 0))
	 /* 之前主要current->euid有错，所以不用它了，以后慢慢解决,包含sched.h就好了。*/
	//if(op == 4 || op == 2)
		return 0;

	/*如果是其他的情况，那么就会拒绝访问*/
	return -EACCES;
}

/*打开文件，我们不用关心它，但也需要注意我们需要用它来增加模块的引用次数*/
int module_open(struct inode *inode, struct file *file)
{
	try_module_get(THIS_MODULE);
	return 0;
}

/*关闭文件，需要用它来减少模块的引用次数*/
int module_close(struct inode *inode, struct file *file)
{
	module_put(THIS_MODULE);
	return 0;
}

/*文件的操作*/
static struct file_operations File_Ops_4_Our_Proc_File = {
	.read = module_output,
	.write = module_input,
	.open = module_open,
	.release = module_close,
};

/*节点的操作,
 * 这里设置了权限控制相关的函数，当然还有其他关于节点的函数，
 * 不过如果我们不设置其它函数应该就只是空值
 * */
static struct inode_operations Inode_Ops_4_Our_Proc_File = {
	.permission = module_permission,
};

/*模块初始化*/
int init_module()
{
	//printk("<1>hello init!\n");
	/*如果不注释掉prink,这里有警告，说声明和代码混淆了*/
	/*先有了printk，然后再定义变量，所以会报警了。
	 * ISO C90不允许在函数中间位置定义变量，所有变量都必须在函数最开始定义。*/

	int rv;
	printk("<1>hello init!\n");
	rv = 0;
	/*建立文件*/
	Our_Proc_File = create_proc_entry(PROC_ENTRY_FILENAME, 0644, NULL);
	Our_Proc_File->owner = THIS_MODULE;
	/*使用前面定义的节点相关操作（集合）*/
	Our_Proc_File->proc_iops = &Inode_Ops_4_Our_Proc_File;
	/*使用前面定义的文件相关操作（集合）
	 * 在前一个例子中，由于定义的操作只有读，所以它可以这样定义：
	 * Our_Proc_File->read_proc = procfile_read;
	 * */
	Our_Proc_File->proc_fops = &File_Ops_4_Our_Proc_File;
	Our_Proc_File->mode = S_IFREG | S_IRUGO | S_IWUSR;
	Our_Proc_File->uid = 0;
	Our_Proc_File->gid = 0;
	Our_Proc_File->size = 80;

	if (Our_Proc_File == NULL)
	{
		rv = -ENOMEM;
		remove_proc_entry(PROC_ENTRY_FILENAME, &proc_root);
		printk(KERN_INFO "Error: Could not initialize /proc/test\n");
	}

	return rv;
}

/*模块卸载*/
void cleanup_module()
{
	remove_proc_entry(PROC_ENTRY_FILENAME, &proc_root);
	printk("<1>bye bye!\n");
}
