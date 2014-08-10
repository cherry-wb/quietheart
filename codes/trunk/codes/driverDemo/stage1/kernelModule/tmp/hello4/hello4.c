/*程序功能：给模块添加授权信息  
 **/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#define DRIVER_AUTHOR "lvkai<quiet_heart000@126.com>"
#define DRIVER_DESC   "My sample driver"

static int __init init_hello_4(void)
{
	printk(KERN_ALERT "Hello, world 4\n");
	return 0;
}

static void __exit cleanup_hello_4(void)
{
	printk(KERN_ALERT "Goodbye, world 4\n");
}

module_init(init_hello_4);
module_exit(cleanup_hello_4);

/* 加上这句话，insmod hello4.ko的时候，在/var/log/syslog中就不会有非授权警告了。
 */
MODULE_LICENSE("GPL");

/*
 *使用modinfo hello4.ko会显示这里的信息。
 **/
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

/*  
 **This module uses /dev/testdevice.  The MODULE_SUPPORTED_DEVICE macro might
 **be used in the future to help automatic configuration of modules, but is 
 **currently unused other than for documentation purposes.
 **/
MODULE_SUPPORTED_DEVICE("testdevice");
