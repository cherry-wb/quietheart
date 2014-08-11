/*程序功能:在/proc目录中创建一个文件,并且读取
 * 可以使用cat /proc/test进行读取。这样将显示相关的信息，在read中定义了.
 * */
/*模块相关*/
#include <linux/module.h>
/*内核相关*/
#include <linux/kernel.h>
/*proc文件系统相关*/
#include <linux/proc_fs.h>

struct proc_dir_entry *Our_Proc_File;

 /*向proc文件中写入数据
 *参数意义：
 * =========
 *1.buffer:(读取的)数据将要插入到buffer,读取的数据应该就会写到这里面
 *2.buffer-location:一个指向字符指针的指针，
 *当你不想使用内核分配的buffer时这很有用
 *3.offset:文件的当前位置
 *4.buffer_length:第一个参数的buffer的大小
 *5.eof:向这里写入一个"l"表示EOF(文件结束符号)
 *6.一个指向数据的指针（在多个/proc/...中使用一个普通的读中很有用??）
 *
 *使用方式和返回值
 *======================
 *返回值是0表示你当前没有额外的信息（到了文件结尾）。
 *返回值是负数表示一种错误的情况。
 *
 *更多的信息
 *====================
 *作者是通过阅读源代码而不是查看文档来知道用这个函数来做什么的。
 *作者查找了什么使用proc_dir-entry结构的get_info域（他使用了find和grep的嘉禾）
 *并且作者发现，它在<kernel source directory>/fs/proc/array.c中被使用。
 *如果有些什么关于内核的东西你不知道的话，你也可以这样做。
 *在linux中，我们有可以随意自由的使用源代码的优势。
 */
ssize_t
procfile_read(char *buffer,
		char **buffer_location,
		off_t offset, int buffer_length, int *eof, void *data)
{

	/*使用的字节数目*/
	int len = 0;
	/*运行这个函数的次数*/
	static int count = 1;

	/*最好把代码执行放在前面的声明的后面否则会有警告*/
	printk(KERN_INFO "inside /proc/test : procfile_read\n");

	/*这里一次性地给出了所有的信息。*/
	if (offset > 0)
	{
		printk(KERN_INFO "offset %d : /proc/test : procfile_read, \
				wrote %d Bytes\n", (int)(offset), len);
		*eof = 1;
		return len;
	}

	/*填充buffer并且获得它的长度*/
	/*这里假设我用cat /proc/test那么我会看到屏幕上面就打印了这里的话*/
	len = sprintf(buffer,
			"For the %d%s time, go away!\n", count,
			(count % 100 > 10 && count % 100 < 14) ? "th" :
			(count % 10 == 1) ? "st" :
			(count % 10 == 2) ? "nd" :
			(count % 10 == 3) ? "rd" : "th");
	count++;

	/*返回长度*/
	printk(KERN_INFO
			"leaving /proc/test : procfile_read, wrote %d Bytes\n", len);
	return len;
}

int init_module()
{
	/*如果不注释掉prink,这里有警告，说声明和代码混淆了*/
	/*先有了printk，然后再定义变量，所以会报警了。
	 * ISO C90不允许在函数中间位置定义变量，所有变量都必须在函数最开始定义。*/
	//printk(KERN_INFO "Hello! In init_module of procfs.ko.\n");

	int rv = 0;
	printk(KERN_INFO "Hello! In init_module of procfs.ko.\n");
	/*这里在/proc中创建(注册)一个文件*/
	Our_Proc_File = create_proc_entry("test", 0644, NULL);
	/*定义读文件时使用刚才定义的函数procfile_read
	 *如果相关的文件操作很多的话可以定义一个struct file_operations
	 *然后给这个结构的变量初始化各种文件操作，最后：
	 *Our_Proc_File->proc_fops = &File_Ops_4_Our_Proc_File;
	 *具体在另一个procfs操作中可以看到这个应用。
	 * */
	Our_Proc_File->read_proc = procfile_read;
	Our_Proc_File->owner = THIS_MODULE;
	Our_Proc_File->mode = S_IFREG | S_IRUGO;
	Our_Proc_File->uid = 0;
	Our_Proc_File->gid = 0;
	Our_Proc_File->size = 37;

	printk(KERN_INFO "Trying to create /proc/test:\n");

	if (Our_Proc_File == NULL)
	{
		rv = -ENOMEM;
		remove_proc_entry("test", &proc_root);
		printk(KERN_INFO "Error: Could not initialize /proc/test\n");
	} else {
		printk(KERN_INFO "Success!\n");
	}

	return rv;
}

void cleanup_module()
{
	/*这里从/proc中移除创建的文件*/
	remove_proc_entry("test", &proc_root);
	printk(KERN_INFO "/proc/test removed\n");
	printk(KERN_INFO "Bye bye!\n");
}
