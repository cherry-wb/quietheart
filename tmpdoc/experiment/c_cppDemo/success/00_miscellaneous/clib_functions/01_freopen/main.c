/*程序功能：
 *这个程序测试freopen函数，这个函数把一个文件和特定的stream相互关联.
 *这里，把文件和标准输出流相关联.
 *结果发现：然后后来的两个对流的写操作都会输入到这个文件中，而不是显示到标准输出屏幕上面了。
 * */
#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *f = freopen("./testFile","a+",stdout);
	fwrite(" how?",1,5,f);
	fwrite(" how?",1,5,stdout);
	return 0;
}
