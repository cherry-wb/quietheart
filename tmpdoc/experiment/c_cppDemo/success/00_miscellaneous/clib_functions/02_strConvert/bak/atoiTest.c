/*程序功能：尝试把各种类型的数据转换成为字符串类型itoa不会?*/
#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
int main(int argc, char *argv[])
{
	int a = 10;
	char str[256];
/*	itoa(a, str, 10);
	printf("the %d to string is %s\n", a ,str);*/
	sprintf(str,"the number is %d\n", a);
	printf(str);
	return 0;
}
