/* 功能：
 * 一个最简单的内核模块
 * 这个函数只演示了模块的加载和卸载函数。

 * 使用方法：
 * 0)编译：
 * $make
 * 1）加载模块：
 * #insmod hello_simple.ko
 * 这样用lsmod|grep hello_simple会发现已经加载了，用cat /proc/modules也行。
 * 2) 卸载模块：
 * #rmmod hello_simple
 * 这样模块会卸载，前面的命令中就找不到hello_simple模块了。
 * 3)查看模块的信息：
 * $modinfo hello_simple.ko
 * 4)查看内核log信息：
 * $cat /var/log/messages
 * $cat /var/log/syslog
 
 *
 * 引用的源代码在/usr/src中,参见Makefile
 * 这里做为一个独立的编译目录来编译这个模块，实际上可以把它添加到内核的源代码目录中进行编译。
 * */

#include<linux/init.h>
#include <linux/module.h>

/*关于模块的信息(可选)，在"linux/module.h"中有定义,在modinfo命令中可以看到这里的信息*/
MODULE_LICENSE("Dual BSD/GPL");/*没有这个，将会受到内核被污染的警告*/
MODULE_AUTHOR("Quiet Heart");
MODULE_DESCRIPTION("This is a simple hello world module.");
MODULE_ALIAS("hello world module");

/*设置加载模块的时候被调用的函数*/
/*模块加载函数一般加上一个__init,动态加载的模块自己有清理工作，不加也没有错*/
/*如果模块编译到内核里面，就没有清理工作了，那么就需要使用这个__init宏了*/
/*这些宏在"linux/init.h中有定义",多看看其中的注释!*/
static int __init hello_init(void)
{
	/*内核空间打印信息的函数，类似printf，不过可以定义输出的级别*/
	/*定义的级别例如KERN_ALERT,在"linux/kernel.h"中*/
	printk(KERN_ALERT "hello world!\n");

	/*模块函数如果初始化成功返回0，若初始化失败，应返回错误码，这样用户程序就能用perror等*/
	/*错误码例如-ENODEV,-ENOMEM等，其定义在"linux/errno.h"中*/
	/*这里假设我返回了5，那么insmod之后echo $?还是0，而在/var/log/syslog中会提醒返回了5*/
	return 0;
}

/*设置卸载模块的时候被调用的函数*/
/*模块卸载函数一般加上一个__exit,动态加载的模块自己有清理工作，不加也没有错*/
/*如果模块编译到内核里面，就没有清理工作了，那么就需要使用这个__exit宏了*/
/*这些宏在"linux/init.h中有定义"*/
static void __exit hello_exit(void)
{
	printk(KERN_ALERT "bye world!");
}

/*用这两个宏指定加载和卸载调用的函数*/
/*定义在"linux/init.h"中*/
module_init(hello_init);
module_exit(hello_exit);
