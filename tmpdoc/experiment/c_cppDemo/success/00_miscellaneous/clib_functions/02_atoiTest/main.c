/*程序功能：
 *将一个数字字符串转化成数字
 * 第一个参数是一个数字，但是是用字符串表示的，把字符串转换为整数。
 * 经过测试，非法的字符串转换成数字0。例如aaa就是非法的。
 * */
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("usage:%s <number>\n",argv[0]);
		return 1;
	}
	int integer = atoi(argv[1]);
	printf("the trans integer is:%d\n", integer);

	char *num = "12345";
	int integer2 = atoi(num);
	printf("the trans integer2 is:%d\n", integer2);
	return 0;
}
