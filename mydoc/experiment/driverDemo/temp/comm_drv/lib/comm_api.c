#include <assert.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <sys/mman.h>
#include <pthread.h>
#include <string.h>
#include "comm_api.h"
#include "../drv/comm_drv.h"

/*Debug switch: 1 to open otherwise close.*/
#ifndef COMM_API_DBG
#define COMM_API_DBG 1
#endif

#if COMM_API_DBG == 1
/*Log functions : It's best to use this to print log!!!*/
/*Example:
*print log:
*a)comm_info("your message.\n");
*b)comm_info("your string:%s, your integer:%d.\n",strvalue,intvalue);
*/
#define comm_info(format, args...) \
    fprintf(stderr, "LIB function:%s, Line:%d.--->"format ,__FUNCTION__, __LINE__ , ##args)
#else
#define comm_info(format, args...)
#endif

/*for assert.*/
#define NDEBUG

/******Internal dclarations******/
static int s_fd[COMM_COUNT];
static int s_opennum = 0;

#define comm_error(format, args...) \
    fprintf(stderr, "Error! " format "\n" , ## args)

/******Internal functions implementations******/

/******Interface implementations******/
int comm_initialize(int dev_num, int block)
{
	int ret = 0;
	int i; 
	/*XXX device name length not up to 16.*/
	char dev_name[16];

	comm_info("\n");
	assert((dev_num < COMM_COUNT ) && (dev_num > -1));

	if(0 == s_opennum)
	{/*XXX The first time to initialize.*/
		for(i = 0; i < COMM_COUNT; ++i)
		{
			s_fd[i] = -1;
		}
	}
	sprintf(dev_name, "/dev/"COMM_DEVICE"%d", dev_num);

	if(-1 == s_fd[dev_num])
	{
		if(COMM_NBLOCK == block)
		{
			if((s_fd[dev_num] = open(dev_name, O_NONBLOCK, O_RDWR)) >= 0)
			{
				++s_opennum;
			}
		}
		else
		{
			if((s_fd[dev_num] = open(dev_name, O_RDWR)) >= 0)
			{
				++s_opennum;
			}
		}
	}
	else
	{
		comm_error("Initialized before.\n");
	}
	if( s_fd[dev_num] < 0)
	{
		comm_error("%s failed.!\n", __FUNCTION__);
		ret = -1;
	}
	return ret;
}

int comm_release(int dev_num)
{
	int ret = 0;
	comm_info("\n");
	if(-1 != s_fd[dev_num])
	{
		close(s_fd[dev_num]);
		--s_opennum;
	}
	else
	{
		comm_error("Needs initialized before.\n");
	}
	return ret;
}

int comm_create(int dev_num, int nblks, int blksz)
{
	int ret = 0;
	comm_info("\n");
	if(-1 != s_fd[dev_num])
	{
		TABLE_INFO tbl_info = {nblks, blksz};
		ioctl(s_fd[dev_num], COMM_CREAT, &tbl_info);
	}
	else
	{
		comm_error("Haven't initialize before %s.!\n", __FUNCTION__);
		ret = -1;
	}
	return ret;
}

int comm_send(int dev_num, const char* src, int count)
{
	int ret = 0;
	comm_info("\n");
	assert(src != NULL);
	if(-1 != s_fd[dev_num])
	{
		DATA_BUF data = {(char*)src, count};
		ret = ioctl(s_fd[dev_num], COMM_SEND, &data);
	}
	else
	{
		comm_error("Haven't initialize before %s.!\n", __FUNCTION__);
		ret = -1;
	}
	return ret;
}

int comm_getlen(int dev_num)
{
	int ret = 0;
	comm_info("\n");
	if(-1 != s_fd[dev_num])
	{
		comm_info("\n");
		ret = ioctl(s_fd[dev_num], COMM_GETLEN);
	}
	else
	{
		comm_info("\n");
		comm_error("Haven't initialize before %s.!\n", __FUNCTION__);
		ret = -1;
	}
	return ret;

}

int comm_receive(int dev_num, char* des, int count)
{
	int ret = 0;
	comm_info("\n");
	assert(des != NULL);
	if(-1 != s_fd[dev_num])
	{
		DATA_BUF data = {des, count};
		ret = ioctl(s_fd[dev_num], COMM_RECEIVE, &data);
	}
	else
	{
		comm_error("Haven't initialize before %s.!\n", __FUNCTION__);
		ret = -1;
	}
	return ret;
}

/******Test functions implementations******/
