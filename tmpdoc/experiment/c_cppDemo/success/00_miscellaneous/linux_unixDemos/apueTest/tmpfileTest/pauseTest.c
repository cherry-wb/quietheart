/*程序功能：测试pause函数的功能，这个函数导致程序挂起，直到收到一个待处理的信号
 * */
#include<signal.h>
#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
	printf("begin to pause\n");
	pause();
	printf("end of pause\n");
	return 0;
}
