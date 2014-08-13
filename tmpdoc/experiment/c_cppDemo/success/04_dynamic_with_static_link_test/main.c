/*功能：
*本程序测试对库的静态链接和动态链接。
*使用说明：
*1)编译：
*$make
*2)清理以前编译结果：
*$make clean
*具体参见Makefile

*以库a和b为例：
*如果同时存在:liba.so liba.a libb.so libb.a
*使用-la -lb选项的时候，会选择动态的liba.so libb.so来进行链接。
*如果想要使用静态库，那么使用链接器的-Bstatic选项,接着-Bstatic选项后面的-l都选择静态库链接了。
*如果既想要静态，又要动态，那么使用链接器-Bstatic和-Bdynamic选项，-Bdynamic意义类似-Bstatic.
*通过man ld可知，-static和-Bstatic应该等价,但是实践发现使用了-static连glibc都不依赖了。
*另外，注意：
*a)链接器的-Bstatic和-Bdynamic需要用gcc的-W1,option来传递，即应该是"gcc -Wl,-Bstatic ***"的形式.
*b)如果最后一个链接选项是-W1,-Bstatic可能会报告错误，
*因为可能libgcc_s.so库没有静态版本的libgcc_s.a.所以最后要有一个-Wl,-Bdynamic
*c)-Wl中，l是link的意思，不是数字
*d)这个程序测试了Makefile中定义CFLAGS变量，这个变量是make内部变量.
*隐含规则中使用了这个CFLAGS,但是显示规则命令中需要手动指定才行.
*/
#include <stdio.h>
#include "myliba.h"
#include "mylibb.h"
int main(int argc, char *argv[])
{
#ifdef MYFLAG
	printf("main flag\n");
#endif
	printf("hello in main()!\n");
	printa();
	printb();
}
