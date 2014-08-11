#include <stdio.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <sys/mman.h>
#include <pthread.h>
#include "cpucomm_api.h"
#include "../drv/cpu1comm_drv.h"

#if 0
/*XXX Define the physical address in user space?*/
#define WORKRAM_PHYS_BASE    0xBFF00000
#define WKRAM_BUF0  (WORKRAM_PHYS_BASE + 0x1000)
#define WKRAM_BUF1  (WORKRAM_PHYS_BASE + 0x1400)
#define BUF_END   (WORKRAM_PHYS_BASE + 0x1800)
#endif

/******Macro Switches******/
/*No copy if __MEM_MAP == 1, 
*i.e. map wkram to user space to avoid copy in kernel.
*/
#define __MEM_MAP 1

/*Debug switch: 1 to open otherwise close.*/
#define CPU1COMM_API_DBG 0

#if CPU1COMM_API_DBG == 1
/*Log functions : It's best to use this to print log!!!*/
/*Example:
*print log:
*a)cpu1comm_info("your message.\n");
*b)cpu1comm_info("your string:%s, your integer:%d.\n",strvalue,intvalue);
*/
#define cpu1comm_info(format, args...) \
	fprintf(stderr, "Function:%s, Line:%d.--->"format ,__FUNCTION__, __LINE__ , ##args)
#else
#define cpu1comm_info(format, args...)
#endif

/******Internal dclarations******/
static pthread_mutex_t send_mutex = PTHREAD_MUTEX_INITIALIZER;
static int used = 0;
#if __MEM_MAP == 1
static char *base_addr;
static void *buf0_addr;
static void *buf1_addr;
static CPU_COMM_RAM wkram;

static int init_wkram();
static int send_wb(const char* buf, size_t count);
static int notify_read();
static int wait_for_send();
static int receive_rb(char *buf, size_t count);
static int notify_write();
static int wait_for_receive();
static int set_cpu1_wlength(int status);
static int get_cpu1_wlength();
static int set_cpu1_wsent(int length);
static int get_cpu1_wsent();
static int get_cpu1_wstatus();
static int set_cpu1_wstatus(int status);
static int set_cpu1_rlength(int status);
static int get_cpu1_rlength();
static int set_cpu1_rsent(int length);
static int get_cpu1_rsent();
static int get_cpu1_rstatus();
static int set_cpu1_rstatus(int status);
static int cpucomm_sync_kram();
static int cpucomm_sync_uram();
static void print_buffer();
static void is_first_used();

/******Internal functions implementations******/
static int init_wkram()
{
	cpu1comm_info("\n");
	wkram.write_buf = (W_BUF*)buf0_addr;
	wkram.write_buf_wp = wkram.write_buf->data;
	wkram.write_buf_rp = wkram.write_buf->data;
	wkram.diablo_cpu1_status = &wkram.write_buf->info;
	cpu1comm_info("buffer 0 address:0x%x\n",wkram.write_buf);
	cpu1comm_info("buffer 0 data address:0x%x\n",wkram.write_buf->data);
	memset(wkram.write_buf, 0, sizeof(W_BUF));//XXX clear??

	wkram.read_buf = (R_BUF*)buf1_addr;
	wkram.read_buf_wp = wkram.read_buf->data;
	wkram.read_buf_rp = wkram.read_buf->data;
	wkram.diablo_cpu0_status = &wkram.read_buf->info;
	cpu1comm_info("buffer 1 address:0x%x\n",wkram.read_buf);
	cpu1comm_info("buffer 1 data address:0x%x\n",wkram.read_buf->data);
	memset(wkram.read_buf, 0, sizeof(R_BUF));//XXX clear first time,but needs kernel info
	return 0;
}

static int send_wb(const char* buf, size_t count)
{
	cpu1comm_info("\n");
	int received = get_cpu1_wsent();
	wkram.write_buf_rp += received;
	if((wkram.write_buf_rp >= wkram.write_buf + sizeof(W_BUF)))
	{
		wkram.write_buf_rp =  wkram.write_buf->data;
	}
	int sent = 0;
	int status;
	status = get_cpu1_wstatus();

	while(count > 0 
		&& wkram.write_buf_wp != wkram.write_buf_rp
		|| count > 0 &&(!status))
	{/*Have data and not full, or have data and empty.*/
	/*Also check again not full.*/
		*(wkram.write_buf_wp++) = *(buf++);
		--count;
		++sent;
		if((wkram.write_buf_wp >= wkram.write_buf + sizeof(W_BUF)))
		{
			wkram.write_buf_wp =  wkram.write_buf->data;
		}
		if(wkram.write_buf_wp == wkram.write_buf_rp)
		{
			set_cpu1_wstatus(1);
		}
		status = get_cpu1_wstatus();
	}
	if(count > 0)
	{
		;
	}
	set_cpu1_wsent(sent);
	return sent;
}

/*XXX read from cpu0's buffer*/
/*Note should excute on cpu1,this used for debug.*/
static int fake_receive_wb(char *buf, size_t count)
{
	cpu1comm_info("\n");
	int received = 0;
	int status = get_cpu1_wstatus();

	while(count > 0 
		&& wkram.write_buf_rp != wkram.write_buf_wp
		|| count > 0 && status)
	{/*Have data required and not full, or have data required and full.*/
	/*Also check again not empty.*/
		*(buf++) = *(wkram.write_buf_rp++);
		if((wkram.write_buf_rp >= wkram.write_buf + sizeof(W_BUF)))
		{
			wkram.write_buf_rp =  wkram.write_buf->data;
		}
		set_cpu1_wstatus(0);
		status = get_cpu1_wstatus();
		--count;
		++received;
	}
	if(count > 0)
	{
		;
	}
	return received;
}

/*XXX generate interrupt to cpu1 to notify data have been write.*/
static int notify_read()
{
	cpu1comm_info("\n");
	int fd=open("/dev/"CPU1COMM_DEVICE,O_RDWR);
	ioctl(fd,CPU1COMM_NOTIFY_READ);
	close(fd);
}

/*XXX continue to send data after cpu1 notify cpu0*/
static int wait_for_send()
{
	cpu1comm_info("\n");
	int fd=open("/dev/"CPU1COMM_DEVICE,O_RDWR);
	ioctl(fd,CPU1COMM_WAIT_FOR_SEND);
	close(fd);
}

/*XXX read from cpu1's buffer*/
/*Note should receive all the data before the buffer is empty!*/
static int receive_rb(char *buf, size_t count)
{
	cpu1comm_info("\n");
	int sent = get_cpu1_rsent();
	wkram.read_buf_wp += sent;
	if((wkram.read_buf_wp >= wkram.read_buf + sizeof(R_BUF)))
	{
		wkram.read_buf_wp =  wkram.read_buf->data;
	}
	int received = 0;
	int status = get_cpu1_rstatus();

	while(count > 0 
		&& wkram.read_buf_rp != wkram.read_buf_wp
		|| count > 0 && status)
	{/*Have data required and not full, or have data required and full.*/
	/*Also check again not empty.*/
		*(buf++) = *(wkram.read_buf_rp++);
		if((wkram.read_buf_rp >= wkram.read_buf + sizeof(R_BUF)))
		{
			wkram.read_buf_rp =  wkram.read_buf->data;
		}
		set_cpu1_rstatus(0);
		status = get_cpu1_rstatus();
		--count;
		++received;
	}
	if(count > 0)
	{
		;
	}
	set_cpu1_rsent(received);
	return received;
}

/*XXX generate interrupt to cpu1 to notify data have been read.*/
static int notify_write()
{
	cpu1comm_info("\n");
	int fd=open("/dev/"CPU1COMM_DEVICE,O_RDWR);
	ioctl(fd,CPU1COMM_NOTIFY_WRITE);
	close(fd);
}

/*XXX continue to receive data after cpu1 notify cpu0*/
static int wait_for_receive()
{
	cpu1comm_info("\n");
	int fd=open("/dev/"CPU1COMM_DEVICE,O_RDWR);
	ioctl(fd,CPU1COMM_WAIT_FOR_RECEIVE);
	close(fd);
}

/*XXX get cpu1 write ring buffer status*/
static int get_cpu1_wstatus()
{
	cpu1comm_info("\n");
	/*return (*(wkram.diablo_cpu1_status)&1);*/
	return wkram.diablo_cpu1_status->status;
}

/*XXX set cpu1 write ring buffer status*/
static int set_cpu1_wstatus(int status)
{/*set last bit to status, and return whole contains length and status.*/
	cpu1comm_info("\n");
	/*
	cpu1comm_info("before set:0x%x\n",*(wkram.diablo_cpu1_status));
	*(wkram.diablo_cpu1_status) &= (~1);
	*(wkram.diablo_cpu1_status) |= status;
	cpu1comm_info("after set:0x%x\n",*(wkram.diablo_cpu1_status));
	return *(wkram.diablo_cpu1_status);
	*/
	wkram.diablo_cpu1_status->status = status;
	return wkram.diablo_cpu1_status->status;
}

static int set_cpu1_wlength(int length)
{
	cpu1comm_info("\n");
	/*
	*(wkram.diablo_cpu1_status) &= 1;
	*(wkram.diablo_cpu1_status) |= (length << 1);
	return *(wkram.diablo_cpu1_status);
	*/
	wkram.diablo_cpu1_status->total_len = length;
	return wkram.diablo_cpu1_status->total_len;
}

static int get_cpu1_wlength()
{
	cpu1comm_info("\n");
	/*return *(wkram.diablo_cpu1_status) >> 1;*/
	return wkram.diablo_cpu1_status->total_len;
}

static int set_cpu1_wsent(int length)
{
	cpu1comm_info("\n");
	wkram.diablo_cpu1_status->sent_len = length;
	return wkram.diablo_cpu1_status->sent_len;
}

static int get_cpu1_wsent()
{
	cpu1comm_info("\n");
	return wkram.diablo_cpu1_status->sent_len;
}


/*XXX get cpu1 read ring buffer status*/
static int get_cpu1_rstatus()
{
	cpu1comm_info("\n");
	/*return (*(wkram.diablo_cpu0_status)&1);*/
	return wkram.diablo_cpu0_status->status;
}

/*XXX set cpu1 read ring buffer status*/
static int set_cpu1_rstatus(int status)
{/*set last bit to status, and return whole contains length and status.*/
	cpu1comm_info("\n");
	/*
	cpu1comm_info("before set:0x%x\n",*(wkram.diablo_cpu0_status));
	*(wkram.diablo_cpu0_status) &= (~1);
	*(wkram.diablo_cpu0_status) |= status;
	cpu1comm_info("after set:0x%x\n",*(wkram.diablo_cpu0_status));
	return *(wkram.diablo_cpu0_status);
	*/
	wkram.diablo_cpu0_status->status = status;
	return wkram.diablo_cpu0_status->status;
}

static int set_cpu1_rlength(int length)
{
	cpu1comm_info("\n");
	/*
	*(wkram.diablo_cpu0_status) &= 1;
	*(wkram.diablo_cpu0_status) |= (length << 1);
	return *(wkram.diablo_cpu0_status);
	*/
	wkram.diablo_cpu0_status->total_len = length;
	return wkram.diablo_cpu0_status->total_len;
}

static int get_cpu1_rlength()
{
	cpu1comm_info("\n");
	/*return *(wkram.diablo_cpu0_status) >> 1;*/
	return wkram.diablo_cpu0_status->total_len;
}

static int set_cpu1_rsent(int length)
{
	cpu1comm_info("\n");
	wkram.diablo_cpu0_status->sent_len = length;
	return wkram.diablo_cpu0_status->sent_len;
}
static int get_cpu1_rsent()
{
	cpu1comm_info("\n");
	return wkram.diablo_cpu0_status->sent_len;
}

/**@brief test if the wkram is the first time used(not the program first run!)*/
static void is_first_used()
{
/*TODO needs kernel ioctl support.*/
	;
}

/**@brief Sync the wkram pointers in the driver from user space.*/
static int cpucomm_sync_kram()
{
	cpu1comm_info("\n");
	int fd=open("/dev/"CPU1COMM_DEVICE,O_RDWR);
	ioctl(fd,CPU1COMM_SYNC_KRAM,&wkram);
	close(fd);
}

/**@brief Sync the wkram points in the user space from driver.*/
static int cpucomm_sync_uram()
{
	cpu1comm_info("\n");
	int fd=open("/dev/"CPU1COMM_DEVICE,O_RDWR);
	ioctl(fd,CPU1COMM_SYNC_URAM,&wkram);
	close(fd);
}

static void print_buffer()
{
	cpu1comm_info("write usr address(w_w), w:0x%x, r:0x%x, w_w:0x%x, w_r:0x%x,r_w:0x%x,r_r:0x%x.\n",
			wkram.write_buf,wkram.read_buf,
			wkram.write_buf_wp, wkram.write_buf_rp,
			wkram.read_buf_wp, wkram.read_buf_rp);
	cpu1comm_info("buffer status,w:%d, r:%d.\n",wkram.write_buf->info.status,wkram.read_buf->info.status);
	cpu1comm_info("buffer total len,w:%d, r:%d.\n",wkram.write_buf->info.total_len,wkram.read_buf->info.total_len);
}

#endif

/******Interface implementations******/
int cpucomm_initialize()
{/*TODO Cann't clear buffer status!!!*/
	cpu1comm_info("\n");
	int fd=open("/dev/"CPU1COMM_DEVICE,O_RDWR);
	if( used < 0 )
	{/*XXX Error, release > initialize.*/
		return -1;
	}
#if __MEM_MAP == 1
	if( 0 == used )
	{/*XXX map only once.*/
		cpu1comm_info("before map, wkram address:0x%x\n",base_addr);
		cpu1comm_info("before map, buffer 0 address:0x%x\n",buf0_addr);
		cpu1comm_info("before map, buffer 1 address:0x%x\n",buf1_addr);
		base_addr = mmap(0,WORKRAM_SIZE,PROT_READ|PROT_WRITE,
				MAP_SHARED,fd,START_OFF);
		buf0_addr = (long)base_addr + BUF0_OFF;
		buf1_addr = (long)base_addr + BUF1_OFF;
		cpu1comm_info("after map, wkram address:0x%x\n",base_addr);
		cpu1comm_info("after map, buffer 0 address:0x%x\n",buf0_addr);
		cpu1comm_info("after map, buffer 1 address:0x%x\n",buf1_addr);

		init_wkram();
		++used;
	}
	cpucomm_sync_uram();/*sync user space pointer from kernel.*/
#if 0
	else
	{
		if(0 == base_addr)
		{
			base_addr = mmap(0,WORKRAM_SIZE,PROT_READ|PROT_WRITE,
					MAP_SHARED,fd,START_OFF);
			buf0_addr = (long)base_addr + BUF0_OFF;
			buf1_addr = (long)base_addr + BUF1_OFF;
		}
		cpucomm_sync_uram();/*sync user space pointer from kernel.*/
	}
#endif
#else
#endif
	/*++used;*/
	close(fd);
	return 0;
}

int cpucomm_release()
{
	cpu1comm_info("\n");
	int fd=open("/dev/"CPU1COMM_DEVICE,O_RDWR);
	/*--used;*/
#if __MEM_MAP == 1
	cpucomm_sync_kram();/*sync user space pointer to kernel.*/
	if(0 == used)
	{/*XXX Never reach here.*/
		munmap(base_addr,WORKRAM_SIZE);
	}
#else
#endif
	close(fd);
}

int cpucomm_send(const char* ptr, int count)
{
	pthread_mutex_lock(&send_mutex);
	cpu1comm_info("\n");
	int fd=open("/dev/"CPU1COMM_DEVICE,O_RDWR);
	int sent = 0;
	int tmp = 0;
#if __MEM_MAP == 1
	if(!ptr)
	{
		return 0;
	}

	set_cpu1_wlength(count);
	do{/*XXX another thread???*/
		tmp = send_wb(ptr, count);
		count -= tmp;
		sent += tmp;
		notify_read();
		if(count > 0)
		{
			wait_for_send();
		}
	}while(count > 0);
#else
	sent = write(fd,ptr,count);
#endif
	close(fd);
	pthread_mutex_unlock(&send_mutex);
	return sent;
}

/*XXX*/
int cpucomm_rcvwait(char* ptr, int* size)
{
	cpu1comm_info("\n");
	int fd=open("/dev/"CPU1COMM_DEVICE,O_RDWR);
#if __MEM_MAP == 1
	/*ioctl(fd,CPU1COMM_WKRAM_RCVWAIT);*/
	*size = get_cpu1_rlength();
#else
#endif
	close(fd);
	return 0;
}

/*XXX Another thread?*/
int cpucomm_rcv(char* des, const char* src, int count)
{
	cpu1comm_info("\n");
	int fd=open("/dev/"CPU1COMM_DEVICE,O_RDWR);
	int received = 0;
	int tmp = 0;

#if __MEM_MAP == 1
	if(!des)
	{
		return 0;
	}
	do{
		tmp = receive_rb(des, count);
		count -= tmp;
		received += tmp;
		notify_write();
		if(count > 0)
		{
			wait_for_receive();
		}
	}while(count > 0);
#else
	read(fd,des,count);
#endif
	close(fd);
	return received;
}

/******Test functions implementations******/
/**@brief Send or write data to buffer0 in kernel.*/
int cpucomm_fake_write(char* ptr, int size)
{
	cpu1comm_info("\n");
	int fd=open("/dev/"CPU1COMM_DEVICE,O_RDWR);
	IOCTL_BUF sbuf={ptr, size};
	cpucomm_sync_uram();
	cpu1comm_info("before write:\n");
	print_buffer();
	cpu1comm_info("data to send is: %s\n", sbuf.data);
	ioctl(fd,CPU1COMM_FAKE_WWRITE,&sbuf);
	close(fd);
	cpucomm_sync_uram();
	cpu1comm_info("after write:\n");
	print_buffer();
}

/**@brief Receive from buffer0 as on cpu1 in kernel.*/
int cpucomm_fake_read(char* des, int count)
{
	cpu1comm_info("\n");
	int fd=open("/dev/"CPU1COMM_DEVICE,O_RDWR);
	IOCTL_BUF sbuf={des, count};
	cpucomm_sync_uram();
	cpu1comm_info("before read:\n");
	print_buffer();
	ioctl(fd,CPU1COMM_FAKE_WREAD,&sbuf);
	cpu1comm_info("data read is: %s\n", sbuf.data);
	close(fd);
	cpucomm_sync_uram();
	cpu1comm_info("after read:\n");
	print_buffer();
}

#if __MEM_MAP == 1
/**@brief write a char to wkram's buffer0 and buffer1 in kernel space.
* In fact, write 'A' in buffer0, write 'B' in buffer1.
*/
int cpucomm_kwrite_test()
{
	cpu1comm_info("\n");
	cpu1comm_info("Write %c to buf0[0], %c to buf1[1]\n",WWRITE_CHAR1,WWRITE_CHAR2);
	int fd=open("/dev/"CPU1COMM_DEVICE,O_RDWR);
	ioctl(fd,CPU1COMM_WWRITE_TEST);
	close(fd);
	return 0;
}

/**@brief Read a char from wkram's buffer0 and buffer1 in user space.*/
int cpucomm_uread_test()
{
	cpu1comm_info("\n");
	cpu1comm_info("buf0address:0x%x,buf0[0]:%c\n",wkram.write_buf->data,wkram.write_buf->data[0]);
	cpu1comm_info("buf0's r pointer address:0x%x,buf0[0]:%c\n",wkram.write_buf_rp,wkram.write_buf_rp[0]);
	cpu1comm_info("buf1address:0x%x,buf1[0]:%c\n",wkram.read_buf->data,wkram.read_buf->data[0]);
	cpu1comm_info("buf1's r pointer address:0x%x,buf1[0]:%c\n",wkram.read_buf_rp,wkram.read_buf_rp[0]);
}

/**@brief write a char to wkram's buffer0 and buffer1 in user space.
* In fact, write 'A' in buffer0, write 'B' in buffer1.
*/
int cpucomm_uwrite_test()
{
	cpu1comm_info("\n");
	cpu1comm_info("Write %c to buf0[0], %c to buf1[1]\n",WWRITE_CHAR1,WWRITE_CHAR2);
	wkram.write_buf->data[0] = WWRITE_CHAR1;
	wkram.read_buf->data[0] = WWRITE_CHAR2;
#if 1
	set_cpu1_wlength(9);
	set_cpu1_rlength(5);
#endif
	return 0;
}

/**@brief Read a char from wkram's buffer0 and buffer1 in kernel.*/
int cpucomm_kread_test()
{
	cpu1comm_info("\n");
	int fd=open("/dev/"CPU1COMM_DEVICE,O_RDWR);
	ioctl(fd,CPU1COMM_RWRITE_TEST);
	close(fd);
}

/**@brief Send or write data to buffer0 in user space.*/
int cpucomm_fake_write2(char* ptr, int count)
{
	cpu1comm_info("\n");
	cpucomm_sync_uram();
	cpu1comm_info("before write:\n");
	print_buffer();
	set_cpu1_wlength(count);
	send_wb(ptr, count);
	cpucomm_sync_kram();
	cpu1comm_info("after write:\n");
	print_buffer();
}

/**@brief Receive from buffer0 as on cpu1 in user space.*/
int cpucomm_fake_read2(char* des, int count)
{
	cpu1comm_info("\n");
	cpucomm_sync_uram();
	cpu1comm_info("before read:\n");
	print_buffer();
	fake_receive_wb(des, count);
	cpucomm_sync_kram();
	cpu1comm_info("after read:\n");
	print_buffer();
}

/**@brief Wait receive from buffer0 as on cpu1 in user space, get the size to receive.*/
int cpucomm_fake_wait(char* ptr, int* size)
{
	cpu1comm_info("\n");
	int fd=open("/dev/"CPU1COMM_DEVICE,O_RDWR);
#if __MEM_MAP == 1
	/*ioctl(fd,CPU1COMM_WKRAM_RCVWAIT);*/
	*size = get_cpu1_wlength();
#else
#endif
	close(fd);
	return 0;
}
#else
int cpucomm_kwrite_test()
{;}
int cpucomm_uread_test()
{;}
int cpucomm_uwrite_test()
{;}
int cpucomm_kread_test()
{;}
int cpucomm_fake_write2(char* ptr, int count)
{;}
int cpucomm_fake_read2(char* des, int count)
{;}
int cpucomm_fake_wait(char* ptr, int* size)
{;}
#endif

/**@brief Only notify the cpu1 that read have done.
* Example:
* notify_read_test();
**/
int notify_read_test()
{
	notify_read();
}

/*@brief Only notify the cpu1 that the write have done.
* Example:
* notify_write_test();
**/
int notify_write_test()
{
	notify_write();
}
