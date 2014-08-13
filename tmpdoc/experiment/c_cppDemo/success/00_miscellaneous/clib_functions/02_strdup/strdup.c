/*程序功能：动态分配一个空间并将复制字符串到动态分配的空间中。
 * 测试函数strdup的功能。
 * extern char *strdup(char *s);
 *功能：复制字符串s
 *说明：返回指向被复制的字符串的指针，所需空间由malloc()分配且可以由free()释放。

 *char *strndup(const char *s, size_t n);
 *功能：类似strdup,不过指定了最多可以拷贝的字符个数。
 *说明：返回指向被复制的字符串的指针，所需空间由malloc()分配且可以由free()释放。
 *如果指定的个数小于原有字符串的长度也会在最后添加一个'\0'.
 * */
#include <stdio.h>
#include <malloc.h>
#include <string.h>
int main(int argc, char *argv[])
{
	char *src = "first";

	//
	char *dst = strdup(src);
	dst[0] = 't';
	printf("the src is:%s\n", src);
	printf("the dst after modify is:%s\n", dst);//tirst
	free(dst);
	dst = NULL;
	
	//指定个数的dup,
	dst = strndup(src,4);
	printf("the dst of strndup is:%s\n", dst);//firs
	free(dst);
	dst = NULL;
	return 0;
}
