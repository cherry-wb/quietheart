#ifndef __CPU1COMM_DRV_H
#define __CPU1COMM_DRV_H

/******Macro Switches******/
/*No copy if __MEM_MAP == 1,
*i.e. map wkram to user space to avoid copy in kernel.
*/
#define __MEM_MAP 1

/*XXX what will be the major?*/
#define CPU1COMMDRV_MAJOR 252
#define CPU1COMM_DEVICE  "cpu1comm"

/******Commands for ioctl.******/
#define CPU1COMM_MAGIC 'C'
#define CPU1COMM_INIT _IOWR(CPU1COMM_MAGIC,0,CPU_COMM_RAM)
#define CPU1COMM_RELEASE _IOWR(CPU1COMM_MAGIC,1,CPU_COMM_RAM)
#define CPU1COMM_WKRAM_RCVWAIT _IO(CPU1COMM_MAGIC,2)
#define CPU1COMM_SEND _IOWR(CPU1COMM_MAGIC,3,IOCTL_BUF)
#define CPU1COMM_RECEIVE _IOWR(CPU1COMM_MAGIC,4,IOCTL_BUF)
#define CPU1COMM_WKRAM_SBUF _IOWR(CPU1COMM_MAGIC,5,char*)
#define CPU1COMM_WKRAM_RBUF _IOWR(CPU1COMM_MAGIC,6,char*)
#define CPU1COMM_WKRAM_STAT _IOWR(CPU1COMM_MAGIC,7,int)

#define CPU1COMM_NOTIFY_READ _IO(CPU1COMM_MAGIC,8)
#define CPU1COMM_WAIT_FOR_SEND _IO(CPU1COMM_MAGIC,9)
#define CPU1COMM_NOTIFY_WRITE _IO(CPU1COMM_MAGIC,10)
#define CPU1COMM_WAIT_FOR_RECEIVE _IO(CPU1COMM_MAGIC,11)
#define CPU1COMM_SYNC_KRAM _IOWR(CPU1COMM_MAGIC,12,CPU_COMM_RAM)
#define CPU1COMM_SYNC_URAM _IOWR(CPU1COMM_MAGIC,13,CPU_COMM_RAM)

/*XXX For debug and test.*/
#define CPU1COMM_FAKE_WWRITE _IO(CPU1COMM_MAGIC,14)
#define CPU1COMM_FAKE_WREAD _IO(CPU1COMM_MAGIC,15)
#define CPU1COMM_WWRITE_TEST _IO(CPU1COMM_MAGIC,16)
#define CPU1COMM_RWRITE_TEST _IO(CPU1COMM_MAGIC,17)
#define WWRITE_CHAR1 'A'
#define WWRITE_CHAR2 'B'
typedef struct {
    char* data;
    int length;
} IOCTL_BUF;


/******Memory map offset******/
/*Whole work ram*/
#define START_OFF 0
#define WORKRAM_SIZE (1<<13) /*8K*/

/*cpu0->cpu1 ring buffer.*/
#define BUF0_OFF 0x0800
#define BUF0_SHIFT 11
#define BUF0_SIZE (1<<BUF0_SHIFT)

/*cpu1->cpu0 ring buffer.*/
#define BUF1_OFF 0x1000
#define BUF1_SHIFT 11
#define BUF1_SIZE (1<<BUF1_SHIFT)

/******Buffer structure******/
#define TIME_SHIFT 2
#define MAX_SEND_TIME (1<<TIME_SHIFT) /*we can send at most 4 times before receive.*/
/*
*1,General communication process on cpu0:
*(1)send data to cpu1:
*(a)on cpu0, read the cpu1 status, if its write buffer is full then wait, or write.
*(b)on cpu0, generate an interrupt to cpu1 after after write its buffer to notify cpu1 to read.
*(c)on cpu1,after cpu1 read, generate interrupt to cpu0 to tell it the data have been read.
*(c)do (a)-(c) until all the data be sent.
*(2)receive data from cpu1:
*(a)on cpu1,read the cpu1 status, if its read buffer is full then wait, or write.
*(b)on cpu1, generate an interrupt to cpu0 after write to notify cpu0 to read.
*(c)on cpu0,in the interrupt handler, receive the data, generate interrupt to cpu1 the data have been read.
*(d)do (a)-(c) until all the data be received.
*
*2,Status check for write and read ring buffer:
*(1)if the two buffer is empty, then their read pointer equals to  write pointer.
*(2)on cpu0, after write to write buffer, its write pointer updated.
*If the read pointer equals to  write pointer again, it means full.
*(3)on cpu1, after read from write buffer, its read pointer updated.
*If it is full, then clear the full flag.
*(4)on cpu1, after write to read buffer, its write pointer updated.
*If the read pointer equals to  write pointer again, it means full.
*(5)on cpu0, after read from read buffer, its read pointer updated.
*If it is full, then clear the full flag.
*
*3,Status check for send and receive cache number:
*(1)When send, write the data to 'next send' area (specified by send_num).
*(2)After send, update the 'next send' area (increase the send_num), and may also 'full flag'.
*(3)When receive, read the data from 'next recv' area (specified by recv_num).
*(4)After receive, update the 'next recv' area (increase the recv_num), and may also 'full flag'.
*(5)The 'full flag' (specified by cache_up) means whether it can send data:
*        if(recv_num == send_num && cache_up == 1) can't send again.
*        if(recv_num == send_num && cache_up == 0) can't receive.
*(6)The related data structure and members are showed mainly as the following figure:
*       +------+------+---------+----+ \
*       | next | next |area size|full| status
*       | recv | send |  array  |flag| space
*       +------+------+---------+----+ /
*       |               data         |\
*       +----------------------------+ \
*       |                  data      |  \
*       +----------------------------+    data space
*       |                    data    |    ring buffer with
*       +----------------------------+    r,w,pointer.
*       |                       data |  /
*       +----------------------------+ /
*       | data                       |/
*       +----------------------------+
*
*x,Note:
*(1)The r,w,pointer (specified by 'xx_buf_wp' and 'xx_buf_rp' where the 'xx' stands for 'write' or 'read') points to the real data in a ring buffer(specified by 'write_buf' and 'read_buf').
*(2)'write_buf' is ring buffer for cpu0->cpu1, 'read_buf' is ring buffer for cpu1->cpu0 .
*(3)The 'recv_num' and 'send_num' can't exceed 'MAX_SEND_TIME' or it will take modular reduction arithematic.
*/
typedef struct {
    struct WB_Inner {
        /*XXX Total size is 32+32+64=128 bits.*/
        /*Offset 0: 32 bits for global info. */
        unsigned total_len: 13; /*XXX 8K max for request.*/
		unsigned sent_len: BUF0_SHIFT;
        unsigned send_flg: 1; /*interrupt type flag for write*/
        unsigned recv_flg: 1; /*interrupt type flag for receive*/
        unsigned used_flg: 1;
        unsigned reserved: 4;
        unsigned status: 1; /*status flag for full or not(the whole buffer).*/

        /*Offset 32: 32 bits for new struct flags.*/
		unsigned recv_num: TIME_SHIFT; /*next receive from here.*/
		unsigned send_num: TIME_SHIFT; /*next send to here*/
        unsigned cache_up: 1; /*status for if can't send.*/
        unsigned reserved_flag: 27;

        /*Offset 64: 16xMAX_SEND_TIME bits for size of array for every cache.*/
        unsigned short size_array[MAX_SEND_TIME];

    } info;
    volatile char data[BUF0_SIZE-128]; /*XXX not all used*/
} W_BUF;

typedef struct {
    struct RB_Inner {
        /*XXX Total size is 32+32+64=128 bits.*/
        /*Offset 0: 32 bits for global info. */
        unsigned total_len: 13; /*XXX 8K max for request.*/
		unsigned sent_len: BUF1_SHIFT;
        unsigned send_flg: 1; /*interrupt type flag for write*/
        unsigned recv_flg: 1; /*interrupt type flag for receive*/
        unsigned used_flg: 1;
        unsigned reserved: 4;
        unsigned status: 1; /*status flag for full or not(the whole buffer).*/

        /*Offset 32: 32 bits for new struct flags.*/
		unsigned recv_num: TIME_SHIFT; /*next receive from here.*/
		unsigned send_num: TIME_SHIFT; /*next send to here*/
        unsigned cache_up: 1; /*status for if can't send.*/
        unsigned reserved_flag: 27;

        /*Offset 64: 16xMAX_SEND_TIME bits for size of array for every cache.*/
        unsigned short size_array[MAX_SEND_TIME];
    } info;
    volatile char data[BUF1_SIZE-128];
} R_BUF;

typedef struct {
    volatile char* write_buf_wp;/*The write pointer of write ring buffer of cpu1.[0,4],write by cpu0.*/
    volatile char* write_buf_rp;/*The read pointer of write ring buffer of cpu1.[0,4],read by cpu1.*/
    volatile struct WB_Inner* diablo_cpu1_status;/*cpu1 write ring buffer status.(Bit[0]--0:not full, 1:full),other bits for len*/
    volatile W_BUF* write_buf;

    volatile char* read_buf_wp;/*The write pointer of read ring buffer of cpu1.[0,1],write by cpu1.*/
    volatile char* read_buf_rp;/*The read pointer of read ring buffer of cpu1.[0,1],read by cpu0.*/
    volatile struct RB_Inner* diablo_cpu0_status;/*cpu1 read ring buffer status.(Bit[0]--0:not full, 1:full),other bits for len*/
    volatile R_BUF* read_buf;
} CPU_COMM_RAM;
#endif
