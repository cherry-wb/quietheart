/*这个程序是对自己建立的这个设备驱动的测试程序，主要测试驱动的ioctl接口*/
#include <stdio.h>
#include <fcntl.h>

/*ioctl command of the driver*/
#define MEM_CLEAR 0x1
int main(int argc, char *argv[])
{
	int fd = open("/dev/mytest",O_RDWR);
	ioctl(fd,MEM_CLEAR);
	return 0;
}
