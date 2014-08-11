/*说明：这里关于ioctl定义的头文件
 * 这里的声明必须在一个头文件里面，因为它们需要被内核模块（chardev.c）
 * 还有调用ioctl的进程（ioctl.c）来使用（知道）。*/
#ifndef CHARDEV_H
#define CHARDEV_H

#include <linux/ioctl.h>

/*主设备号。我们不能够再使用动态注册了，因为ioctl需要知道这个主设备号*/
#define MAJOR_NUM 100

/*设置设备驱动的消息(相当于向设备文件写)*/
#define IOCTL_SET_MSG _IOR(MAJOR_NUM, 0, char *)
/*_IOR的意思是，我们创建一个ioctl命令号，用于从用户进程向内核模块传递信息。
 * 第一个参数，MAJOR_NUM是我们使用的主设备号。
 * 第二个参数，是命令号码(可能有不同的号码表示不同的含义)
 * 第三个参数，是我们想要从进程到内核获取的类型?
 * */

/*获得设备驱动的消息(相当于从设备文件读)*/
#define IOCTL_GET_MSG _IOR(MAJOR_NUM, 1, char *)
/*这个IOCTL用于输出，也就是从设备驱动获取信息.
 * 然而，我们仍然需要一个缓存来存放消息，这个是由进程来分配的。*/

/*获得消息的第n个字节*/
#define IOCTL_GET_NTH_BYTE _IOWR(MAJOR_NUM, 2, int)
/*这个IOCTL既可用于读又用于写。
 *它从用户接收一个号码n,然后返回消息第n个字节Message[n]*/

/*设备文件名称*/
#define DEVICE_FILE_NAME "char_dev"

#endif
