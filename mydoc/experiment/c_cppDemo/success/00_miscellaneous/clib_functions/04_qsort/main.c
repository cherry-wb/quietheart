/*程序功能：使用qsort对一个随机的任意类型的数组进行进行排序
 * 函数原型：
 * #include <stdlib.h>
 *void qsort(void *base, size_t nmemb, size_t size,
 *            int(*compar)(const void *, const void *));
 * 参数含义：
 * base:待排序数组首地址。
 * nmemb:待排序的元素数目。
 * size:每个元素的大小。
 * compar：一个比较函数返回负数、0、整数，分别表示小于、等于、大于。
 * */
#include <stdlib.h>
#include <stdio.h>

typedef struct MyStruct
{
	int num;
}MyStruct;
int myCmp(const void *op1, const void *op2);

int main(int argc, char *argv[])
{
	MyStruct test[10];
	int i;
	for(i = 0; i < 10; ++i)
	{
		test[i].num = rand() %50;//产生一个50以内的随机数
	}

	printf("the num before sort is:\n");
	for(i = 0; i < 10; ++i)
	{
		printf("%d,", test[i].num);
	}
	printf("\n");

	qsort(test, 10, sizeof(test[0]), myCmp);//开始排序

	printf("the num after sort is:\n");
	for(i = 0; i < 10; ++i)
	{
		printf("%d,", test[i].num);
	}
	printf("\n");

	return 0;
}

int myCmp(const void *op1, const void *op2)
{
	MyStruct *t1 = (MyStruct*)op1;
	MyStruct *t2 = (MyStruct*)op2;
	return (t1->num > t2->num ? 1:0);
}
