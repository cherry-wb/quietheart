/*程序功能：这里实验可变参数的函数,以及可变参数的宏的特性.
*可变参数函数void my_sum(int count, ...);
*这个函数的功能是计算多个整数的和。
*其中count是将要求和的整数的数目。
*其它的参数是可变的,其中第一个参数是char*的参数，用于提示。
*后面的参数分别是待求和的整数，一共count个。
*/

#include <stdarg.h>
#include <stdio.h>

void my_sum(int count, ...);

int main(int argc, char *argv[])
{
	int count = 5;
	printf("compute sum of %d numbers.\n",count);
	my_sum(count,"the sum of numbers is:", 1, 2, 3, 4, 5);
	return 0;
}

void my_sum(int count, ...)
{
	//将要用来存放需要的某个可变参数的指针的信息
	va_list ap;
	char *prompt;
	int sum = 0;

	//开始的初始化，其中ap含有指向可变参数的指针的信息，count是当前函数中最后一个非可变的参数(这样才能定位).
	va_start(ap, count);
	
	//获取并返回下一个可变参数的值，第一个参数是ap不用说了，第二个参数是要获取的参数的类型。
	//根据文档，如果类型指定错误了，或者没有下一个可变参数了，那么返回的结果是随机的。
	prompt = va_arg(ap, char*);
	printf("%s\n", prompt);
	
	int i;
	for(i = 0; i < count; ++i)
	{
		sum += va_arg(ap, int);
	}
	
	//使用完可变参数之后要用这个来释放资源
	va_end(ap);
	printf("%d\n",sum);
	
}
