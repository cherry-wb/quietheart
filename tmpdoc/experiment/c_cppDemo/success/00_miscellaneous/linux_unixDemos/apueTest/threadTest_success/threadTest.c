/*程序功能：一个简单的多线程程序
 *三个线程描述如下：
 *第一个将字符c写为'a'然后打印，
 *第二个将字符c写为'b'然后打印，
 *第三个将字符c写为'c'然后打印，
 *三个线程都是一个死循环，不断的写自己的字符
 *但是三者互相同步，最终导致屏幕不断依次输出'a','b','c'.
 * */
#include<stdio.h>

/*exit*/
#include<stdlib.h>
#include<pthread.h>
/*线程id*/
pthread_t ntid1;
pthread_t ntid2;
pthread_t ntid3;

/*信号*/
pthread_mutex_t f_lock;

/*缓冲*/
char c = 'c';
/*打印线程id,没有使用*/
void
printids(const char *s)
{
	pid_t      pid;
	pthread_t  tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid,
			(unsigned int)tid, (unsigned int)tid);
}

/*线程函数*/
void *
thr_fn1(void *arg)
{
//	printids("new thread: ");
	while(1)
	{
		if(c == 'c')
		{
			pthread_mutex_lock(&f_lock);
			c = 'a';
			printf("%c \n", c);
			pthread_mutex_unlock(&f_lock);
		}
		else
		{
			continue;
		}
	}
	return((void *)0);
}
void *
thr_fn2(void *arg)
{
//	printids("new thread: ");
	while(1)
	{
		if(c == 'a')
		{
			pthread_mutex_lock(&f_lock);
			c = 'b';
			printf("%c \n", c);
			pthread_mutex_unlock(&f_lock);
		}
		else
		{
			continue;
		}
	}
	return((void *)0);
}
void *
thr_fn3(void *arg)
{
//	printids("new thread: ");
	while(1)
	{
		if(c == 'b')
		{
			pthread_mutex_lock(&f_lock);
			c = 'c';
			printf("%c \n", c);
			pthread_mutex_unlock(&f_lock);
		}
		else
		{
			continue;
		}
		//printf("%s\n", (char*)arg);
	}
	return((void *)0);
}

int
main(int argc, char *argv[])
{
	int err;

	if (pthread_mutex_init(&f_lock, NULL) != 0)
	{
		perror("mutex is out\n");
	}
	/*thread a*/
	err = pthread_create(&ntid1, NULL, thr_fn1, NULL);
	if (err != 0)
	{
		perror("create thread error!\n");
		exit(0);
	}
	//pthread_detach(ntid1);

	/*thread b*/
	err = pthread_create(&ntid2, NULL, thr_fn2, NULL);
	if (err != 0)
	{
		perror("create thread error!\n");
		exit(0);
	}
	pthread_detach(ntid2);

	/*thread b*/
	err = pthread_create(&ntid3, NULL, thr_fn3, NULL);
	if (err != 0)
	{
		perror("create thread error!\n");
		exit(0);
	}
	pthread_detach(ntid2);

	printids("main thread:");
	sleep(1);
	pthread_join(ntid1,NULL);
	pthread_join(ntid2,NULL);
	pthread_join(ntid3,NULL);
	pthread_mutex_destroy(&f_lock);
	exit(0);
}
