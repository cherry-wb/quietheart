/* 功能：
 * 一个具有参数的内核模块
 * 这个函数演示了带有参数的模块。

 * 使用方法：
 * 0)编译：
 * make
 * 1）加载模块：
 * #insmod hello_param.ko
 * 这样会使用默认的参数
 * #insmod hello_param.ko welcome="hello" num=8
 * 在目录/sys/module/hello_param/parameters/中就有相应的参数welcome和num
 * 
 * 2) 卸载模块：
 * #rmmod hello_param
 * 这样模块会卸载，前面的命令中就找不到hello_simple模块了。
 
 * 3)查看模块都有哪些参数：
 * $modinfo hello_param.ko
 *
 * 引用的源代码在/usr/src中,参见Makefile
 * 这里做为一个独立的编译目录来编译这个模块，实际上可以把它添加到内核的源代码目录中进行编译。
 * */

#include<linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Quiet Heart");
MODULE_DESCRIPTION("This is a simple hello world module.");
MODULE_ALIAS("hello world module");

/*将要成为参数的变量*/
static char * welcome = "This is value of param char*.";
static int num = 5;
/*数组参数有待研究*/
/*static int array[5] = {1,2,3,4,5};*/

static int __init hello_init(void)
{
	/*使用参数*/
	printk(KERN_INFO "welcome word:%s\n",welcome);
	printk(KERN_INFO "int param:%d\n",num);
	/*
	for(int i = 0; i < 5; ++i)
	{
		printk(KERN_INFO "arrary[%d]:%d\n",i,arrary[i]);
	}
	*/

	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "bye world!");
}

module_init(hello_init);
module_exit(hello_exit);

/*在这里指定参数，这些宏定义在"linux/module.h中包含的moduleparam.h中,具体有什么类型需要分析相应的宏
 *如果使用其他的功能的话需要查看这个头文件。*/
/*第一个参数是变量名，第二参数是类型，具体什么类型分析宏的解析过程可知*/
/*第三个参数是权限，定义在"linux/stat.h"表明谁可以存取这个参数*/

/*模块参数在sysfs中表示. 若权限为0, 就无sysfs项. 否则, 它出现在 /sys/module[5]下面, 
 *根据网上资料：带有给定的权限. 使用 S_IRUGO 作为参数可以被所有人读取, 但是不能改变; 
 *S_IRUGO|S_IWUSR 允许 root 来改变参数. 
 *注意, 如果一个参数被sysfs修改, 你的模块看到的参数值也改变了, 但是你的模块没有任何其他的通知. 
 *你应当不要使模块参数可写, 除非你准备好检测这个改变并且因而作出反应.*/
module_param(welcome,charp,S_IRUGO);
module_param(num,int,S_IRUGO);
/*module_param(array,int,5,S_IRUGO);*/
