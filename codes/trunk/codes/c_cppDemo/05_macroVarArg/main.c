/*程序功能：这个程序是使用“可变参数宏”的简单例子.
C99标准中新增了可变参数列表的内容. 不光是函数, 函数宏中也可以使用可变参数列表.
#define name(args, ...) tokens
#define name(...) tokens
"..."代表可变参数列表, 如果它不是仅有的参数, 那么它只能出现在参数列表的最后. 调用这样的函数宏时, 传递给它的参数个数要不少于参数列表中参数的个数(多余的参数被丢弃).
通过__VA_ARGS__来替换函数宏中的可变参数列表. 注意__VA_ARGS__只能用于函数宏中参数中包含有"..."的情况.

实践发现：
#define my_printf(format, ...) printf(format, __VA_ARGS__)这样会报告错误。
#define my_printf(format, args...) printf(format, ## args)这样就不会有错误了（gcc风格）。

(应该是编译器的特性吧)
*/

#include <stdio.h>
#define my_printf(...) fprintf(stderr,__VA_ARGS__)
int main(int argc, char *argv[])
{
	char *str="my print";
	int test = 5;
	my_printf("Hello!This is my print function\n");
	my_printf("Hello! This is %s , test integer is:%d \n", str, test);
	return 0;
}
