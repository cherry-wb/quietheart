/*程序功能：测试回车
 * 测试结果：
 * 回车'\r'就是回到本行的开头，并没有换行。
 * */
#include <stdio.h>
int main(int argc, char *argv[])
{
	printf("hello,\rhi\n");
	return 0;
}
