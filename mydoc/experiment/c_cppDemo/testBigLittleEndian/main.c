//判断是little endian还是big endian
//这里给出两个方法，第二个方法使用了联合，封装在一个函数中进行实现。
#include <stdio.h>
int is_big_endian(void)
{
	printf("judge by %s:\n",__FUNCTION__);
	union
	{
		long l;
		char bytes[sizeof(long)];
	} u;
	u.l = 1;
	return (u.bytes[sizeof(long)-1]==1);
}

int main(int argc, char *argv[])
{
	int a = 0x11223344;
	if((char)a == 0x11)
	{//低地址存高字节
		printf("big endian!\n");
	}
	printf("%x\n",(int)(char)a);

	short b = 0x1122;
	if((char)b == 0x22)
	{//低地址存低字节
		printf("little endian!\n");
	}
	//强转之后的地址，一定是从低开始算。
	printf("%x\n",(int)(char)b);

	if(is_big_endian())
	{
		printf("is big endian. \n");
	}
	else
	{
		printf("is little endian. \n");
	}
	printf("hello\n");
}
