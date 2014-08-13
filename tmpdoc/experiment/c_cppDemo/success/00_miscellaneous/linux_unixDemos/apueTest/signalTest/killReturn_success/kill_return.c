/*程序功能：测试kill发送信号的情况：
 * 1）发送信号后，是立即返回还是在信号处理函数返回之后返回。
 * 2）发送信号后，相应的回调函数是否被重置，即如果再发送是否还调用先前的回调函数
 *测试结果:
 *1）必须处理完回调函数之后kill才返回，如果回调函数死循环，那么kill不会返回
 *2）发送信号之后，相应的回调函数不会被重置（尽管书上说重置）
 * */
#include<stdio.h>

/*SIGUSR1,SIGUSR2,kill,signal*/
#include<signal.h>
/*SIGUSR1和SIGUSR2信号共同的回调处理函数*/
static void sig_usr(int);

int
main(void)
{
	/*连接两个信号SIGUSR1和SIGUSR2的回调函数*/
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		perror("can't catch SIGUSR1");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		perror("can't catch SIGUSR2");

	/*给自己发送信号*/
	/*先发送两次信号，看看是否信号接收一次就重新置位了*/
	kill(getpid(), SIGUSR2);
	kill(getpid(), SIGUSR2);

	/*SiGUSR的回调函数是死循环*/
	kill(getpid(), SIGUSR1);
	printf("kill returned\n");
	return 0;
}

static void
sig_usr(int signo)
{
	if (signo == SIGUSR1)
	{
		printf("received SIGUSR1\n");
		/*进入死循环*/
		while(1)
		{
			sleep(1);
			printf("in sig_usr\n");
		}
	}
	else if (signo == SIGUSR2)
	{
		printf("received SIGUSR2\n");
		/*睡眠2秒*/
		sleep(2);
	}
	else
		fprintf(stderr,"received signal %d\n", signo);
}
