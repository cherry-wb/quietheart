//功能：测试空函数指针的引用
//结果：出现段错误
#include <stdio.h>
void (*pf)(int a);
void test(int a)
{
	printf("hello test!\n");
}

int main(int argc, char *argv[])
{
	printf("hello!\n");
	int a = 1;
	//pf = NULL;//段错误
	pf = test;
	pf(a);
	return  0;
}
