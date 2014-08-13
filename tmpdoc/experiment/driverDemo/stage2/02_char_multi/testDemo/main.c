/*这个程序是对自己建立的这个设备驱动的测试程序，主要测试:
 *驱动的ioctl接口
 *从驱动读
 *向驱动写
 */
#include <stdio.h>
#include <fcntl.h>

/*用于_IO宏*/
#include <linux/fs.h>

/*ioctl command of the driver*/
#define GLOBALMEM_MAGIC 'D'
#define MEM_CLEAR _IO(GLOBALMEM_MAGIC,0)
int main(int argc, char *argv[])
{
	if(1 == argc)
	{
		printf("Usage:%s [clear |read |write ]\n", argv[0]);
		return 1;
	}
	/*2 == argc*/ 
	int fd0 = open("./mytest0",O_RDWR);
	int fd1 = open("./mytest1",O_RDWR);
	if(0 == strcmp(argv[1],"clear"))
	{
		ioctl(fd0,MEM_CLEAR);
		ioctl(fd1,MEM_CLEAR);
		printf("Clear data in fd0 and fd1.\n");
		return 0;
	}
	else if(0 == strcmp(argv[1],"read"))
	{
		char buf[7] = {-1,};
		read(fd0,buf,7);
		printf("Read result of fd0 is %s\n",buf);
		read(fd1,buf,7);
		printf("Read result of fd1 is %s\n",buf);
		return 0;
	}
	else if(0 == strcmp(argv[1],"write"))
	{
		write(fd0,"hello0\n",8);
		printf("Write to fd0 is %s\n","hello0");
		write(fd1,"hello1\n",8);
		printf("Write to fd1 is %s\n","hello1");
		return 0;
	}
	else
	{
		printf("parameter error!\n");
		return 1;
	}
	return 0;
}
