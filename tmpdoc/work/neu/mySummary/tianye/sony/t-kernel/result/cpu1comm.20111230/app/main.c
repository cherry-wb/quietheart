#include <stdio.h>
#include <unistd.h>
#include "../lib/cpucomm_api.h"

/*Log functions : It's best to use this to print log!!!*/
/*Example:
*(1)print log:
*a)cpu1comm_info("your message.\n");
*b)cpu1comm_info("your string:%s, your integer:%d.\n",strvalue,intvalue);
*
*(2)not print:
* please set DBG_LOG_ON to 0.
*/
#define DBG_LOG_ON 1
#if DBG_LOG_ON == 1
#define cpu1comm_info(format, args...) \
    fprintf(stderr, "Function:%s, Line:%d.--->"format ,__FUNCTION__, __LINE__ , ##args)
#else
#define cpu1comm_info(format, args...)
#endif
int main(int argc, char* argv[]) {
    char send_str[] = "send data";
    char recv_str[10] = {'\0',};
    int count = sizeof(send_str);
    int rcv_len;
    cpucomm_initialize();
#if 0
    /*Test:memory map*/
    cpu1comm_info("\n");
    cpucomm_kwrite_test();
    cpucomm_uread_test();
    cpu1comm_info("\n");
    cpu1comm_info("\n");
    cpucomm_uwrite_test();
    cpucomm_kread_test();
    cpu1comm_info("\n");
#endif
#if 0
    /*Test:send on cpu0, and simulate receive on cpu1, in kernel space.*/
    cpu1comm_info("str to send is:%s\n", send_str);
    cpucomm_fake_write(send_str, sizeof(send_str));
    cpucomm_fake_read(recv_str, sizeof(send_str));
    cpu1comm_info("received str is:%s\n", recv_str);
#endif
#if 0
    /*Test:send on cpu0, and simulate receive on cpu1, in user space(without copy in kernel).*/
    cpu1comm_info("str to send is:%s\n", send_str);
    cpucomm_fake_write2(send_str, count);
    cpucomm_fake_read2(recv_str, count);
    cpu1comm_info("received str is:%s\n", recv_str);
#endif
#if 0
    /*Test:send on cpu0(in kernel), and simulate receive on cpu1(user space).*/
    cpu1comm_info("str to send is:%s\n", send_str);
    cpucomm_fake_write(send_str, count);
    cpucomm_fake_read2(recv_str, count);
    cpu1comm_info("received str is:%s\n", recv_str);
#endif
#if 0
    /*Test send on cpu0(in user space), and simulate receive on cpu1(kernel space).*/
    cpu1comm_info("str to send is:%s\n", send_str);
    cpucomm_fake_write2(send_str, count);
    cpucomm_fake_read(recv_str, count);
    cpu1comm_info("received str is:%s\n", recv_str);
    cpucomm_release();
#endif
#if 0
    /*Test receive wait return length.*/
    cpu1comm_info("str to send is:%s\n", send_str);
    cpucomm_fake_write2(send_str, count);
    cpu1comm_info("length to send is:%d\n", count);
    cpucomm_fake_wait(NULL, &rcv_len);
    cpu1comm_info("length to receive is:%d\n", rcv_len);
    cpucomm_fake_read2(recv_str, rcv_len);
    cpu1comm_info("received str is:%s\n", recv_str);
#endif
#if 1
    /*Test any thing.*/
    //notify_read_test();
    cpucomm_send(send_str, sizeof(send_str));
    //cpucomm_uwrite_test();
    //cpucomm_kread_test();
    //sleep(1);
    //cpucomm_uread_test();
    //notify_write_test();
    cpucomm_rcvwait(NULL, &rcv_len);
    cpu1comm_info("receive length:%d\n", rcv_len);
    cpucomm_rcv(recv_str, NULL, rcv_len);
    cpu1comm_info("receive str is:%s\n", recv_str);
#endif
#if 0
    /*Test stardard use.*/
    /*TODO*/
    cpucomm_initialize();
    cpucomm_send(send_str, sizeof(send_str));
    cpucomm_rcvwait(NULL, &rcv_len);
    cpucomm_rcv(recv_str, NULL, rcv_len);
#endif
    cpucomm_release();
    return 0;
}
