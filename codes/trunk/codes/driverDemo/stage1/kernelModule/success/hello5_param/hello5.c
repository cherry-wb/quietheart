/*
 *程序功能：编写一个可以接受参数的内核模块
 *测试的方法：
 1)$insmod hello5.ko
 这样使用默认值。
 2)$insmod hello5.ko myint=10 mystring="good"
 这样输出的就是你设置的参数myint和mystring了
 3)$insmod hello5.ko myint=10
 这样，只有myint使用的是你设置的值
 4)$insmod hello5.ko mystring="good"
 这样，只有mystring使用的是你设置的值

 实践之后发现卸载的时候使用下面两个都行：
 rmmod hello5
 rmmod hello5.ko
 **/
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("QuietHeart");

//static short int myshort = 1;
static int myint = 420;
//static long int mylong = 9999;
static char *mystring = "blah";
//数组怎么传？
//int myshortArray[4];
//MODULE_PARM (myintArray, "3-9i");

/*modult_param(foo, int, 0000)
 *第一个参数代表参数的名字
 *第二个参数代表参数的类型
 *最后一个参数代表访问权限,
 *(for exposing parameters in sysfs (if non-zero) at a later stage)
 * */
/*MODULE_PARM_DESC(foo, description)
 * 这个宏的作用是对某一个变量进行描述,modinfo中会显示这个描述.
 * 第一个参数是变量的名字
 * 第二个参数是对变量的描述
 * */
//module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
//MODULE_PARM_DESC(myshort, "A short integer");
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An integer");
//module_param(mylong, long, S_IRUSR);
//MODULE_PARM_DESC(mylong, "A long integer");
module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "A character string");

static int __init hello_5_init(void)
{
	printk(KERN_ALERT "Hello, world 5\n=============\n");
	//printk(KERN_ALERT "myshort is a short integer: %hd\n", myshort);
	printk(KERN_ALERT "myint is an integer: %d\n", myint);
	//printk(KERN_ALERT "mylong is a long integer: %ld\n", mylong);
	printk(KERN_ALERT "mystring is a string: %s\n", mystring);
	return 0;
}

static void __exit hello_5_exit(void)
{
	printk(KERN_ALERT "Goodbye, world 5\n");
}

module_init(hello_5_init);
module_exit(hello_5_exit);
