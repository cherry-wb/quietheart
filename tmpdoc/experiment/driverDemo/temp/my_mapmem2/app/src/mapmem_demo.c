/**
* @mainpage Main page of usage of mapmem demo.
*	- @subpage mapmem_drv About mapmem driver.
*	- @subpage mapmem	About mapmem device api.
*	.
* Description: 
*
* This Shows how to use the mem map driver.
*
* Author: quiet_heart000@126.com
* Copyright 2011
*/
#include <stdio.h>

//mmap
#include <sys/mman.h>//mmap
#include <unistd.h>//sysconf
#include <fcntl.h>//file open
#include <stdio.h>//printf

//thread
/*exit*/
#include<stdlib.h>
#include<pthread.h>
#include <signal.h>

#include "../lib/mapmem.h"

//debug 1 for w/r, 2 for send/receive.
#define MY_DEBUG_WR 1
#define MY_DEBUG_SR 2
#define MY_DEBUG MY_DEBUG_WR

void *g_usr_vir_addr = NULL;
int         g_rcv_flag = 0;
pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t g_wait = PTHREAD_COND_INITIALIZER;
sigset_t    g_mask;

void *thr_receive(void *arg)
{
    int err, signo;
    while(1)
    {
        err = sigwait(&g_mask, &signo);
        if (err != 0)
        {
            perror("sigwait failed\n");
            exit(1);
        }

        switch (signo)
        {
            case SIGIO:
                pthread_mutex_lock(&g_lock);
                printf("In child thread: received signal %s!!\n",strsignal(signo));
                g_rcv_flag = 1;
#if MY_DEBUG == MY_DEBUG_WR
				char *filename = "/dev/"__DEVICE_NAME__;
				int fd = open(filename,O_RDONLY);
				char buf[10] = {0,};
				read(fd,buf,sizeof(buf));
				printf("read from device:%s",buf);
#elif MY_DEBUG == MY_DEBUG_SR
				//receive(g_usr_vir_addr, receivebuf, receivelen);
#else
#endif
                pthread_mutex_unlock(&g_lock);
                pthread_cond_signal(&g_wait);
                return(0);

            default:
                printf("In child thread: unexpected signal %d\n",signo);
                exit(1);
        }
    }
    return((void *)0);
}



int main(int argc, char *argv[])
{
/*Command argument*/
	if(argc != 2)
	{
		//write(STDOUT_FILENO,"hello\n",6);
		printf("usage:%s <filename>\n",argv[0]);
		return 1;
	}

	char *filename = argv[1];
	int fd = open(filename,O_RDONLY);
	printf("the file to be mapped is:%s\n",filename);

/*Map to user vir addr from mapmem device...*/
#if MY_DEBUG == MY_DEBUG_WR
#elif MY_DEBUG == MY_DEBUG_SR
	int offset = 0;
	int realOffset = 0 & ~(sysconf(_SC_PAGE_SIZE) - 1);//XXX
	int length = __MAPMEM_SIZE__;
	int realLen = length+offset-realOffset;//XXX

	g_usr_vir_addr = mmap(NULL, realLen,PROT_READ | PROT_WRITE,MAP_SHARED,fd,realOffset);
#else
#endif

/*Send and receive*/
	pthread_t ntid_receiver;
	int         err = 0;
	sigset_t    oldmask;
	int oflags;

	sigemptyset(&g_mask);
	sigaddset(&g_mask, SIGIO);
	if ((err = pthread_sigmask(SIG_BLOCK, &g_mask, &oldmask)) != 0)
	{
		perror("SIG_BLOCK error\n");
		exit(1);
	}

#if MY_DEBUG == MY_DEBUG_WR
#elif MY_DEBUG == MY_DEBUG_SR
	fcntl(fd, F_SETOWN, getpid());
	oflags = fcntl(STDIN_FILENO, F_GETFL);
	fcntl(STDIN_FILENO, F_SETFL, oflags | FASYNC);
#else
#endif
    err = pthread_create(&ntid_receiver, NULL, thr_receive, g_usr_vir_addr);
    if (err != 0)
    {
        perror("create receive thread error!\n");
        exit(0);
    }
    pthread_detach(ntid_receiver);

	printf("In main thread: begin to send!!\n");
#if MY_DEBUG == MY_DEBUG_WR
	write(fd, "hello!", sizeof("hello!"));
	pthread_kill(ntid_receiver,SIGIO);
#elif MY_DEBUG == MY_DEBUG_SR
	send(g_usr_vir_addr, "hello!", sizeof("hello!"));
#else
#endif

    pthread_mutex_lock(&g_lock);
    while (g_rcv_flag == 0)
    {
        pthread_cond_wait(&g_wait, &g_lock);
    }
    pthread_mutex_unlock(&g_lock);

    printf("In main thread: know that child thread received SIGIO!!\n");

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
        perror("SIG_SETMASK error\n");
        exit(1);
    }

	//map to physical address.
	//unsigned long phy_addr = user_virt_to_phys((unsigned long )g_usr_vir_addr);
	//printf("The address in user space is:%ld\nThe physical address is:%ld\n",g_usr_vir_addr,phy_addr);
	close(fd);
#if MY_DEBUG == MY_DEBUG_WR
#elif MY_DEBUG == MY_DEBUG_SR
	munmap(g_usr_vir_addr,realLen);
#else
#endif
	return 0;
}
