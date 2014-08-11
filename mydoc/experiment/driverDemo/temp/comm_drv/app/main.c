#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include<pthread.h>
#include "../lib/comm_api.h"

/*Log functions : It's best to use this to print log!!!*/
/*Example:
*(1)print log:
*a)comm_info("your message.\n");
*b)comm_info("your string:%s, your integer:%d.\n",strvalue,intvalue);
*
*(2)not print:
* please set DBG_LOG_ON to 0.
*/
#ifndef DBG_LOG_ON
#define DBG_LOG_ON 1
#endif
#if DBG_LOG_ON == 1
#define comm_info(format, args...) \
    fprintf(stderr, "APP function:%s, Line:%d.--->"format ,__FUNCTION__, __LINE__ , ##args)
#else
#define comm_info(format, args...)
#endif


int nblks = 16;
int blksz = 32;

static int single_thread_test();

#define INPUT_LEN 32
pthread_t ntid1;
pthread_t ntid2;
pthread_t ntid3;
static int device1=1;
static int device2=2;
static void printids(const char *s);
static void * thr_fn0(void *arg);
static void * thr_fn1(void *arg);
static void * thr_fn2(void *arg);
static int multi_thread_test();

int main(int argc, char* argv[])
{
#if 0
	single_thread_test();
#else
	multi_thread_test();
#endif
    return 0;
}

static int single_thread_test()
{
    char send_str[] = "send data";
    int send_count = sizeof(send_str);
	int sent = 0;
    char recv_str[10] = {'\0',};
    int rcv_len;
	int received = 0;
	int device = 0;/*which device [0,31]*/
	int times = 1;
    comm_initialize(device,COMM_NBLOCK);

#if 1
/*XXX test create*/
    comm_info("Test create start.\n");
	comm_create(device, nblks, blksz);
    comm_info("Test create end.\n");
#endif

#if 1
/*XXX test send and receive one time.*/
    comm_info("Test send start.\n");
    comm_info("Send data is:%s\n",send_str);
	sent = comm_send(device, send_str, send_count);
    comm_info("Sent length is:%d\n",sent);

    comm_info("Test receive start.\n");
	do
	{
		rcv_len = comm_getlen(device);
	}while(rcv_len < 0);
	comm_receive(device, recv_str, rcv_len);
    comm_info("Received data is:%s\n",recv_str);
    comm_info("Received length is:%d\n",rcv_len);
#endif

#if 1
/*XXX test send and receive many times*/
	while(times<6)
	{
		comm_info("times:%d.\n",times);
		send_str[0]+=1;
		times +=1;
		comm_info("Test send start.\n");
		comm_info("Send data is:%s\n",send_str);
		sent = comm_send(device, send_str, send_count);
		comm_info("Sent length is:%d\n",sent);

		comm_info("Test receive start.\n");
		do
		{
			rcv_len = comm_getlen(device);
		}while(rcv_len < 0);
		comm_receive(device, recv_str, rcv_len);
		comm_info("Received data is:%s\n",recv_str);
		comm_info("Received length is:%d\n",rcv_len);
	}
#endif

    comm_release(device);
	comm_info("Test end.\n");
}

static int multi_thread_test()
{
	printids("main thread:");
	int err;

#if 1
	/*Process:
	*1,thread0 is thr_fn0, which reads input from standard input.
	*2,thread1 and thread2 waits for data.
	*3,thread0 send the input string to thread1, and reversed input string to thread2.
	*4,thread1 and thread2 receives data and print them.
	*5,go back to step 2.
	*/
    comm_initialize(device1,COMM_BLOCK);
    comm_initialize(device2,COMM_BLOCK);
	err = pthread_create(&ntid1, NULL, thr_fn0, NULL);
	if (err != 0)
	{
		perror("create thread error!\n");
		return err;
	}
	/*pthread_detach(ntid1);*/

	err = pthread_create(&ntid2, NULL, thr_fn1, NULL);
	if (err != 0)
	{
		perror("create thread error!\n");
		return err;
	}
	/*pthread_detach(ntid2);*/

	err = pthread_create(&ntid3, NULL, thr_fn2, NULL);
	if (err != 0)
	{
		perror("create thread error!\n");
		return err;
	}
	/*pthread_detach(ntid3);*/

	pthread_join(ntid1,NULL);
	pthread_join(ntid2,NULL);
	pthread_join(ntid3,NULL);
    comm_release(device1);
    comm_release(device2);
	comm_info("Test end.\n");
#endif
}

static void printids(const char *s)
{
	pid_t      pid;
	pthread_t  tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid,
			(unsigned int)tid, (unsigned int)tid);
}

static void * thr_fn0(void *arg)
{
	printids("new thread0: ");
	char input_buf1[INPUT_LEN];
	char input_buf2[INPUT_LEN];
	int i;
	int str_len;
	int sent;
	comm_create(device1, nblks, blksz);
	comm_create(device2, nblks, blksz);

	/*read input from standard I/O, one line at a time, input_buf2 reverses input_buf1.*/
	while(NULL != fgets(input_buf1, INPUT_LEN-1, stdin))
	{
		str_len = strlen(input_buf1);
		input_buf1[str_len - 1] = '\0';
		str_len = strlen(input_buf1);
		for(i = 0; i < str_len; ++i)
		{
			input_buf2[i] = input_buf1[str_len-1-i];
		}
		input_buf2[i] = '\0';
		comm_info("Thread0 send input1:%s, length is:%d\n", input_buf1, str_len);
		sent = comm_send(device1, input_buf1, str_len);
		comm_info("Thread0 sent length is:%d\n", sent);

		comm_info("Thread0 send input2:%s, length is:%d\n", input_buf2, str_len);
		sent = comm_send(device2, input_buf2, str_len);
		comm_info("Thread0 sent length is:%d\n", sent);
	}
}

static void * thr_fn1(void *arg)
{
	int str_len;
	int rcv_len;
	char rcv_buf[INPUT_LEN];

	printids("new thread1: ");

	do
	{
		do
		{
			rcv_len = comm_getlen(device1);
		}while(rcv_len < 0);
		rcv_len = comm_receive(device1, rcv_buf, rcv_len);
		comm_info("Thread1 received data is:%s\n",rcv_buf);
		comm_info("Thread1 received length is:%d\n",rcv_len);
	}while(1);
}

static void * thr_fn2(void *arg)
{
	int str_len;
	int rcv_len;
	char rcv_buf[INPUT_LEN];

	printids("new thread2: ");

	do
	{
		do
		{
			rcv_len = comm_getlen(device2);
		}while(rcv_len < 0);
		rcv_len = comm_receive(device2, rcv_buf, rcv_len);
		comm_info("Thread2 received data is:%s\n",rcv_buf);
		comm_info("Thread2 received length is:%d\n",rcv_len);
	}while(1);
}
