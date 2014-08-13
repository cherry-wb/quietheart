/*本函数的功能：
 * 一个最简单的内核模块
 * 这里加载和清除模块的printk打印的语句应该在/var/log/messages中。
 * 如果在纯命令终端下面那么不但在这个文件中有所体现，而且标准输出也会显示。
 * 这里有个问题：只有init里面的语句在messages中，但是cleanup的没有。
 * 两者的语句在标准输出中都有。？？？
 * 但是在/var/log/syslog中都有打印。
 * 使用方法：
 * 1）加载模块：
 * insmod hello.ko
 * 这样用lsmod|grep hello会发现已经加载了，用cat /proc/modules也行。
 * 2) 卸载模块：
 * rmmod hello
 * 这样模块会卸载，前面的命令中就找不到hello模块了。
 * 源代码在/usr/src中
 * */
#include<linux/module.h>
#include<linux/kernel.h>

int init_module(void)
{/*载入模块的时候调用的函数*/
	/*这里KERN_ALERT是一个优先级，其宏定义为："<1>"
	 * printk实际有多个优先级，定义在 kernel.h 中*/
	printk("<1>hello,module1!!\n");
	return 0;
	/*说返回非0则无法加载但是也在syslog里面发现了信息了？messages好像没有*/
	//return 1;
}

void cleanup_module(void)
{/*卸载模块的时候调用的函数*/
	printk(KERN_ALERT"goodbye,module1!!\n");
}
