//功能：测试异步通知的输入输出信号。
//问题：为什么会不断地输出信号???
//#include <sys/types.h>
//#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#define MAX_LEN 100
void input_handler(int num)
{
	static int a = 0;
	//signal(SIGIO, SIG_IGN);
	printf("input signal(sigio):%s received %d times\n",strsignal(num),++a);
	//signal(SIGIO, input_handler);
}
main()
{
	int oflags;
	signal(SIGIO, input_handler);
	fcntl(STDIN_FILENO, F_SETOWN, getpid());
	oflags = fcntl(STDIN_FILENO, F_GETFL);
	fcntl(STDIN_FILENO, F_SETFL, oflags | FASYNC);
	while (1);
}

