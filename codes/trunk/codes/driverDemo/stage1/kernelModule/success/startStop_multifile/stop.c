/*程序功能:一个多文件的内核模块程序举例
 *stop.c
 **/

#include <linux/kernel.h>
#include <linux/module.h>

void cleanup_module()
{
		printk("<1>Short is the life of a kernel module\n");
}
