#ifndef __COMM_DRV_H
#define __COMM_DRV_H
/*XXX what will be the major?*/
#define COMMDRV_MAJOR 250
#define COMM_DEVICE  "comm" /*device names are: /dev/comm[0-31]*/
#define COMM_COUNT 32 /*minor range is [0,31]*/

/******Commands for ioctl.******/
struct table_info
{/*XXX typedef*/
	unsigned ti_nblks;
	unsigned ti_blksz;
};

struct data_buf
{
    void* data;
    int length;
};

typedef struct table_info TABLE_INFO;
typedef struct data_buf DATA_BUF;
#define COMM_MAGIC 'C'
#define COMM_CREAT _IOWR(COMM_MAGIC,0,TABLE_INFO)
#define COMM_SEND _IOWR(COMM_MAGIC,1,DATA_BUF)
#define COMM_RECEIVE _IOWR(COMM_MAGIC,2,DATA_BUF)
#define COMM_GETLEN _IO(COMM_MAGIC,3)
#define COMM_CLEAR _IO(COMM_MAGIC,4)
#define COMM_IOC_MAXNR 4


#endif
