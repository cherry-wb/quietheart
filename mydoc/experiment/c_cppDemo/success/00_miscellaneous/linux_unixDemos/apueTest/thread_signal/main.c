/*
程序功能：
使用一个线程来处理主线程发送过来的异步信号。处理之后通知主线程。
涉及的知识点：线程控制，信号发送和控制，互斥量和条件同步。
具体为：
0）存在两个线程，主线程发送信号，子线程接收信号并反馈给主线程，子线程由主线程创建。
1）两个线程通过互斥锁控制共享资源quitflag，通过条件变量进行同步。
2) 主线程给子线程发送信号并等待反馈。(发送之前用户可以通过键盘的C-c发送消息SIGINT在子线程中终止进程)
3）子线程等待，若收到信号打印字符串，之后给主线程反馈。
4）主线程收到反馈同样也打印一个字符串。
编译过程：
1)gcc main.c -lpthread
*/
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <stdlib.h>

int         quitflag = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t wait = PTHREAD_COND_INITIALIZER;

void *thr_fn(void *arg)
{
    int err, signo;
    while(1)
	{
		/*子线程等待信号*/
		sigset_t    *mask = (sigset_t*)arg;
		err = sigwait(mask, &signo);
		if (err != 0)
		{
			perror("sigwait failed\n");
			exit(1);
		}

		/*子线程处理信号*/
		switch (signo)
		{
			case SIGQUIT:
				pthread_mutex_lock(&lock);
				sleep(3);
				printf("In child thread: received SIGQUIT!!\n");
				quitflag = 1;
				pthread_mutex_unlock(&lock);
				pthread_cond_signal(&wait);
				return(0);

			default:
				printf("In child thread: unexpected signal %d\n", signo);
				exit(1);
		}
	}
}

int main(int argc, char *argv[])
{
	int         err;
	sigset_t    mask;
	sigset_t    oldmask;
	pthread_t   tid;

	/*设置线程处理的信号，将它们阻塞这样本主线程就不处理那些需要子线程处理的信号了*/
	sigemptyset(&mask);
	sigaddset(&mask, SIGQUIT);//代码中发送的消息
	sigaddset(&mask, SIGINT);//可以通过键盘"C-c"发送的消息，非期望的。
	if ((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0)
	{
		perror("SIG_BLOCK error\n");
		exit(1);
	}

	/*创建子线程,子线程将等待信号*/
	err = pthread_create(&tid, NULL, thr_fn, &mask);
	if (err != 0)
	{
		perror("can't create thread\n");
		exit(1);
	}
	pthread_detach(tid);//不关心子线程退出状态，这样子线程结束后就会释放它自己的资源。
	
	/*给子线程发送信号*/
	printf("In main thread: begin to send SIGQUIT...!!\n");
	sleep(3);
	pthread_kill(tid,SIGQUIT);
	printf("In main thread: SIGQUIT sended!!\n");

	/*等待子线程处理结束通知*/
	pthread_mutex_lock(&lock);
	while (quitflag == 0)
	{
		pthread_cond_wait(&wait, &lock);
	}
	pthread_mutex_unlock(&lock);

	/*子线程信号处理完毕*/
	sleep(3);
	printf("In main thread: know that child thread received SIGQUIT!!\n");

	/*恢复之前的信号*/
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		perror("SIG_SETMASK error\n");
		exit(1);
	}
	return 0;
}
