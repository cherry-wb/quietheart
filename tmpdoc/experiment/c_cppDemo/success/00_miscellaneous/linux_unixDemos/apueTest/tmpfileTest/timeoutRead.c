/*程序功能：输入的时候，三秒内不输入，那么每3秒就提示一次，直到输入了为止。
 * 这里还连接了定时的alarm信号。
 * */
#include<signal.h>
#include<stdio.h>
#include<unistd.h>

#define MAXLINE 10
static void sig_alrm(int);

int main(void)
{
	int     n;
	char    line[MAXLINE];

	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		//err_sys("signal(SIGALRM) error");
		perror("signal(SIGALRM) error");

	alarm(3);
	if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
		//err_sys("read error");
		perror("read error");
	alarm(0);

	write(STDOUT_FILENO, line, n);
	return 0;
}

static void sig_alrm(int signo)
{
	/* nothing to do, just return to interrupt the read */
	alarm(3);
	printf("timeout\n");
}
