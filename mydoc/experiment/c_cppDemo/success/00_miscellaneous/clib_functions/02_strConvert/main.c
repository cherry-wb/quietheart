/*程序功能：字符串和数字之间的转换。
 * 包括：
 * #include <stdlib.h> //这个是头文件
 * 1)把字符转换整数
 * long atoi(char *);  
 *
 * 2)把字符转换成浮点
 * double atof(char *);
 *
 * 3)把整数转换成字符
 * int sprintf(char *str, const char *format, ...);
 * //char *itoa(int value, char *string, int radix);//把整数转为字符串这里没有所以用sprintf
 * */
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	//字符串转整数（还有atol未实践）
	char *str1 = "123";
	int str1Int;
	str1Int = atoi(str1);
	printf("after convert str1=\"123\",int num is: %d\n",str1Int);

	//字符串转double
	char *str2 = "3.3020";
	double str2Double;
	str2Double = atof(str2);
	printf("after convert str1=\"3.3020\",double num is: %lf\n",str2Double);

	//整数转字符串
	int num = 456;
	char str3Num[10];
	//itoa(num,str3Num,10);
	sprintf(str3Num, "%d", 456);
	printf("after convert num=456,str value is: \"%s\"\n",str3Num);
}
