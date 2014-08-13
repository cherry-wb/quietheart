/*程序功能：创建一个proc文件，如果多个程序同时打开这个文件就让它们都睡眠阻塞，
 * 只保留一个不睡眠。
 * */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
/*用于把进程睡眠或者唤醒*/
#include <linux/sched.h> 
#include <asm/uaccess.h>

/*这里我们保存最后一次接收到的消息，用来证明我们可以处理我们的输入*/
#define MESSAGE_LENGTH 80
static char Message[MESSAGE_LENGTH];

static struct proc_dir_entry *Our_Proc_File;
#define PROC_ENTRY_FILENAME "sleep"

/*读取数据
 * 这里，由于我们使用的是文件操作结构，所以我们只能使用标准读取函数,参数如下：
 * file:这个文件的结构可以参见include/linux/fs.h
 * buf:这里是我们读取到的消息的存放的缓存
 * len:这里是接收缓存buf的大小
 * offset:这里暂时没有用到，应该是表示文件指针偏移量的变量*/
static ssize_t module_output(struct file *file,
			     char *buf, 
			     size_t len,
			     loff_t * offset)
{
	static int finished = 0;
	int i;
	char message[MESSAGE_LENGTH + 30];

	/*如果到达文件结尾，返回0*/
	if (finished)
	{
		finished = 0;
		return 0;
	}

	sprintf(message, "Last input:%s\n", Message);
	/*读取过程，把数据从内核空间message[i]拷贝到用户空间buf这样用户就读取到了数据*/
	for (i = 0; i < len && message[i]; i++)
		put_user(message[i], buf + i);

	finished = 1;
	/*返回读取的字符数目*/
	return i;
}

/*写入函数
 *这个函数用于当用户程序写这个文件的时候，从用户程序处获取输入，参数如下：
 *file:将要写的文件本身
 *buf:存放将要写入的数据
 *length:存放写缓存buf的长度
 *offset:没有用到，应该是文件偏移指针
 * */
static ssize_t module_input(struct file *file,
			    const char *buf,
			    size_t length,
			    loff_t * offset)
{
	int i;

	/*写的过程，这里把数据从用户程序空间buf拷贝到内核的空间Message*/
	for (i = 0; i < MESSAGE_LENGTH - 1 && i < length; i++)
		get_user(Message[i], buf + i);
	Message[i] = '\0';

	/*返回写入的字符数目*/
	return i;
}

/*如果文件已经被其他程序打开则这个变量为1*/
int Already_Open = 0;

/*需要我们的这个文件的进程队列*/
DECLARE_WAIT_QUEUE_HEAD(WaitQ);

/*打开文件
 * 当/proc内的我们的文件被打开的时候调用这个函数*/
static int module_open(struct inode *inode, struct file *file)
{
	/*如果文件设置了O_NONBLOCK标记，则表示进程不会等待。
	 * 即，如果文件已经是打开的，那么进程不会阻塞而是立即返回一个-EAGAIN错误*/
	if ((file->f_flags & O_NONBLOCK) && Already_Open)
		return -EAGAIN;

	/*这里应该使用这个函数，因为如果一个进程在内核的模块中处于循环的状态，
	 * 这个内核的模块就不应该被移走了。*/
	try_module_get(THIS_MODULE);


	/*如果文件是打开的状态，那么就等待直到该文件被关闭.*/
	while (Already_Open)
	{
		int i, is_sig = 0;

		/*这个函数将会把当前的进程，或者是任何的系统调用
		 * （这里我们的就是一个系统调用）置为sleep.当有其他调用wake_up(&WaitQ)
		 * 的时候，或者有一个信号的时候（例如Ctrl-C）这个函数就会继续执行。
		 * 应该只有当关闭文件的时候，module_close会进行这个操作*/
		wait_event_interruptible(WaitQ, !Already_Open);
		/*当我们由于收到了一个没有被阻塞的信号而被唤醒的时候，
		 * 将会返回-EINTR(系统调用失败).这样就允许进程被杀掉或者停止了*/


		/*这里相对于2.2.*有所变化。信号现在占据两个字(64比特位)，并且被存放
		 * 在一个包含两个无符号长整数的数组中。现在我们需要在if中进行两次检查
		 *
		 * 因为不能保证将来不会用大于64比特位，这个代码应该在所有的情况下都行*/
		for (i = 0; i < _NSIG_WORDS && !is_sig; i++)
			is_sig =
			    current->pending.signal.sig[i] & ~current->
			    blocked.sig[i];

		if (is_sig)
		{/*如果收到了信号??*/
			/*减少引用计数
			 * 这里使用modult_put(THIS_MODULE)是非常重要的。
			 * 当进程的open被中断的时候，就不再有相应的close调用了。
			 * 如果我们这里不减少使用计数，那么这将一直是一个正数，
			 * 我们没有办法把这个数变成0了，这将导致产生一个无法卸载的模块，
			 * 这个模块就只能在重启机器的时候被卸载了。*/
			module_put(THIS_MODULE);
			return -EINTR;
		}
	}

	/*至此执行这句话之前，Already_Open必然是0*/
	Already_Open = 1;

	/*返回0表示允许访问（打开）*/
	return 0;
}

/*关闭文件
 * 当我们的/proc中的文件被关闭的时候调用这个函数
 * */
int module_close(struct inode *inode, struct file *file)
{
	Already_Open = 0;

	/* 
	 * Wake up all the processes in WaitQ, so if anybody is waiting for the
	 * file, they can have it.
	 */
	/*这里把所有的在WaitQ中的进程唤醒，当有等待这个文件的进程存在的时候，
	 * 他们将"收到这个唤醒"*/
	wake_up(&WaitQ);

	/*减少引用计数*/
	module_put(THIS_MODULE);

	/*返回0表示关闭成功*/
	return 0;
}

/*这个函数用来确定允许操作的权限条件，如果返回非0则不允许
 *相关的值：
 *0-执行
 *2-写入
 *4-读取
 *这里才真正检查文件的操作，ls -l返回的权限仅仅是一个参考的引用，
 *通过这里可以把ls -l的权限覆盖.
 * */
static int module_permission(struct inode *inode, int op, struct nameidata *nd)
{
	/*任何用户可以读取，但是只有根用户可以写入*/
	if (op == 4 || (op == 2 && current->euid == 0))
		return 0;

	/*不允许访问*/
	return -EACCES;
}

/*用于注册/proc内的文件的相关结构，包含了所有相关的函数*/

/*我们/proc文件的操作结构，保存了其他人想要操作我们文件时相应的函数指针。
 * 如果把指针设置为空，表示不进行任何操作。
 * */
static struct file_operations File_Ops_4_Our_Proc_File = {
	.read = module_output,
	.write = module_input,
	.open = module_open,
	.release = module_close,
};

/*对我们的文件的关于Inode方面的操作信息.*/
static struct inode_operations Inode_Ops_4_Our_Proc_File = {
	.permission = module_permission,	/* check for permissions */
};

/*初始化模块
 * 注册/proc文件*/
int init_module()
{
	int rv = 0;
	Our_Proc_File = create_proc_entry(PROC_ENTRY_FILENAME, 0644, NULL);
	Our_Proc_File->owner = THIS_MODULE;
	Our_Proc_File->proc_iops = &Inode_Ops_4_Our_Proc_File;
	Our_Proc_File->proc_fops = &File_Ops_4_Our_Proc_File;
	Our_Proc_File->mode = S_IFREG | S_IRUGO | S_IWUSR;
	Our_Proc_File->uid = 0;
	Our_Proc_File->gid = 0;
	Our_Proc_File->size = 80;

	if (Our_Proc_File == NULL) {
		rv = -ENOMEM;
		remove_proc_entry(PROC_ENTRY_FILENAME, &proc_root);
		printk(KERN_INFO "Error: Could not initialize /proc/test\n");
	}

	return rv;
}

/*卸载模块调用
 * 这里反注册相关/proc中的文件。如果仍然有进程在WaitQ中等待则这个操作是危险的，
 * 因为他们在open函数里面而模块将要卸载了。以后会介绍如何避免这种情况。*/
void cleanup_module()
{
	remove_proc_entry(PROC_ENTRY_FILENAME, &proc_root);
}
