#ifndef __COMM_API_H
#define __COMM_API_H
__BEGIN_DECLS

/*User interfaces.*/
/** 
 * @brief Initialize. 
 * @param[IN] dev_num the number of device to be initialized for use.
 * @param[IN] block whether block when cann't operate the buffer. The value 0 for nonblock, or block.
 * Note:dev_num range is [0,31].
 * @return 0 if success, or else -1.
 */
enum {COMM_NBLOCK=0,COMM_BLOCK=1};
int comm_initialize(int dev_num, int block);

/** 
 * @brief Release current device in use.
 * @param[IN] dev_num the number of device to be released.
 * @return 0 if success, or else -1.
 */
/*XXX needs parameter for special device?*/
int comm_release(int dev_num);

/** 
 * @brief Create message buffer. 
 * Note:create the buffer only at the first time when opening or it will ignore the next create action.
 * @param[IN] dev_num the number of device.
 * @param[IN] nblks number of blocks in table buffer list.
 * @param[IN] blksz bytes of each block in table buffer list.
 * @return 0 if success, or else -1.
 */
int comm_create(int dev_num, int nblks, int blksz);

/**
 * @brief Send data pointed by 'src' with length 'count'.
 * @param[IN] dev_num the number of device.
 * @return length of data be sent or error.
*/
int comm_send(int dev_num, const char* src, int count);

/**
 * @brief Get the length of msg to be received.
 * @param[IN] dev_num the number of device.
 * @return the length of data to be received or else <0.
*/
int comm_getlen(int dev_num);

/**
 * @brief Receive data with length 'count' to 'des'.
 * @param[IN] dev_num the number of device.
 * @param[OUT] des the address where received data store.
 * @param[IN] count the count of data to be received.
 * @return count of data be received or error.
*/
int comm_receive(int dev_num, char* des, int count);

#if 0
/** @brief Wait to get the length of data to receive, return length stored in 'size'.
*Note:'ptr' now have no use. (set to NULL).
*/
int cpucomm_rcvwait(char* ptr, int* size);

/** @brief Receive data with length 'count' to 'des'.
*Note:'src' now have no use. (set to NULL).
*/
int cpucomm_rcv(char* des, const char* src, int count);

/*Miscellaneous tests.*/
int cpucomm_fake_write(char* ptr, int size);
int cpucomm_fake_read(char* des, int count);
int cpucomm_fake_write2(char* ptr, int count);
int cpucomm_fake_read2(char* des, int count);
int cpucomm_fake_wait(char* ptr, int* size);
int cpucomm_kwrite_test();
int cpucomm_uread_test();
int cpucomm_uwrite_test();
int cpucomm_kread_test();
int notify_read_test();
int notify_write_test();
#endif

__END_DECLS
#endif
