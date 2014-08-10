/*这个程序是对自己建立的这个设备驱动的测试程序，主要测试驱动的ioctl接口*/
#include <stdio.h>
#include <fcntl.h>

/*用于_IO宏*/
#include <linux/fs.h>

/*ioctl command of the driver*/
#define GLOBALMEM_MAGIC 'D'
#define MEM_CLEAR _IO(GLOBALMEM_MAGIC,0)
int main(int argc, char *argv[])
{
	int fd = open("/dev/mytest",O_RDWR);
	ioctl(fd,MEM_CLEAR);
	return 0;
}
