/*程序功能:一个多文件的内核模块举例
 * start.c
 **/

#include <linux/kernel.h>
#include <linux/module.h>

int init_module(void)
{
		printk("Hello, world - this is the kernel speaking\n");
			return 0;
}
