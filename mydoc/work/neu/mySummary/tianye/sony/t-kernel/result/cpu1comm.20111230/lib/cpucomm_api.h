#ifndef __CPUCOMM_API_H
#define __CPUCOMM_API_H
__BEGIN_DECLS

/*User interfaces.*/
/** @brief Initialize the memory at first time. */
int cpucomm_initialize();

/** @brief Release resource(note:no use). */
int cpucomm_release();

/** @brief Send data pointed by 'ptr' with length 'count'.
*Note: Length to send and receive should smaller than 1 << (sizeof(int) -1)
*/
int cpucomm_send(const char* ptr, int count);

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

__END_DECLS
#endif
