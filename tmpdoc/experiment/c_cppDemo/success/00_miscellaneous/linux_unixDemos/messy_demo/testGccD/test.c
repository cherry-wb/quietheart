/*程序功能：
这个程序实际就是测试gcc的-D选项，查看Makefile即可知道，通过这个选项，可以临时给程序在编译之前定义一个宏。
而这个宏原来在代码中不存在，这个特性经常用于打开某个宏开关。
*/
#include<stdio.h>

int main(int argc, char *argv[])
{
	int i;
#ifdef MY
	printf("ok, you can define in the gcc command\n");
#if MY==1
	printf("ok, the value of macro MY is 1\n");
#endif
#else
	printf("define nothing\n");
#endif
	return 0;
}
