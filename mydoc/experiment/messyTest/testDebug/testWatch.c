/*这个程序查看调试运行过程中某个变量如果改变的话就会中断*/
#include<stdio.h>

void changeValue(int *x)
{
	int i = 0;
	for(i = 0; i < 10; ++i)
	{
		if(5 == i)
		{
			*x = 5;
		}
	}
}


int main(int argc, char* argv[])
{
	printf("begin test\n");

	int a = 3;
	changeValue(&a);

	printf("test end\n");
	return 0;
}
