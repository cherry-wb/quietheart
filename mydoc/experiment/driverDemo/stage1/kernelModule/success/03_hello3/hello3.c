/*  
 *功能：带有参数和__init,__initdata以及__exit宏的模块。
 *这三个宏在动态加载模块是无效的，因为动态加载模块的清理由自己来做，但是编译进内核就需要了。
 *具体可以参见"linux/init.h"中的注释。
 *    */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_ALERT */
#include <linux/init.h>		/* Needed for the macros */

static int hello3_data __initdata = 3;

static int __init hello_3_init(void)
{
	printk(KERN_ALERT "Hello, world %d\n", hello3_data);
	return 0;
}

static void __exit hello_3_exit(void)
{
	printk(KERN_ALERT "Goodbye, world 3\n");
}

module_init(hello_3_init);
module_exit(hello_3_exit);


