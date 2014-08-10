/*本程序功能：
 * 可以使用模块初始化函数自定义名称的例子
 *
 **/
/*所有模块都需要*/
#include <linux/module.h>

/*KERN_ALERT需要的*/
#include <linux/kernel.h>       

/*所有宏需要的*/
#include <linux/init.h>         

static int __init hello_2_init(void)
{
	printk(KERN_ALERT "Hello, world 2\n");
	return 0;
}

static void __exit hello_2_exit(void)
{
	printk(KERN_ALERT "Goodbye, world 2\n");
}

/*使用这两个语句，这样我们就可以利用自己自定义名称的初始化和释放函数了*/
module_init(hello_2_init);
module_exit(hello_2_exit);

