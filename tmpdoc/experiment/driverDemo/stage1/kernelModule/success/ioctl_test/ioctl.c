/*程序功能：运行这个程序，将调用main中指定的ioctl操作设备*/
/*这个是用户进程，使用ioctl来控制内核模块.
 * 至今，我们能够使用cat来输出和输出。
 * 但是现在，我们需要用ioctl的功能来写我们的进程。*/

/*问题，不知道为什么printf和exit处有警告
 * 但是包含了stdio.h之后，printf处就没有警告了。
 * 包含了stdlib.h之后，exit处也没有警告了.*/

/*设备细节，例如ioctl号码和主设备文件*/
#include "chardev.h"

/*open*/
#include <fcntl.h>
/* exit */
#include <unistd.h>
/* ioctl */
#include <sys/ioctl.h>

/*printf*/
#include<stdio.h>
/*exit*/
#include<stdlib.h>


/*用于ioctl调用的函数*/

void
ioctl_set_msg(int file_desc, char *message)
{/*调用ioctl来设置消息*/
	int ret_val;

	ret_val = ioctl(file_desc, IOCTL_SET_MSG, message);

	if (ret_val < 0)
	{
		printf("ioctl_set_msg failed:%d\n", ret_val);
		exit(-1);
	}
}

void
ioctl_get_msg(int file_desc)
{/*调用ioctl来读取消息*/
	int ret_val;
	char message[100];

	/*注意：这里是危险的，因为我们没有告诉内核能够写多少，所以有可能缓存溢出。
	 * 在一个实际的产品程序中，我们应该有两个ioctls，一个用来告诉内核缓存大小，
	 * 一个用来提供填充的缓存。
	*/
	ret_val = ioctl(file_desc, IOCTL_GET_MSG, message);

	if (ret_val < 0)
	{
		printf("ioctl_get_msg failed:%d\n", ret_val);
		exit(-1);
	}

	printf("get_msg message:%s\n", message);
}

void
ioctl_get_nth_byte(int file_desc)
{/*循环调用读取指定位置的字符，好像是把所有消息也读出来并且打印了*/
	int i;
	char c;

	printf("get_nth_byte message:");

	i = 0;
	while (c != 0)
	{
		c = ioctl(file_desc, IOCTL_GET_NTH_BYTE, i++);

		if (c < 0)
		{
			printf
				("ioctl_get_nth_byte failed at the %d'th byte:\n",
				 i);
			exit(-1);
		}

		putchar(c);
	}
	putchar('\n');
}

/*主函数：调用ioctl函数。*/
main()
{
	int file_desc, ret_val;
	char *msg = "Message passed by ioctl\n";

	/*打开设备文件*/
	file_desc = open(DEVICE_FILE_NAME, 0);
	if (file_desc < 0)
	{
		printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
		exit(-1);
	}

	/*循环读取并打印设备文件消息信息的每个字符*/
	ioctl_get_nth_byte(file_desc);
	/*获得设备文件的消息信息,并打印出来*/
	ioctl_get_msg(file_desc);
	/*设置设备文件的消息信息为msg指定的内容*/
	ioctl_set_msg(file_desc, msg);

	/*关闭设备文件*/
	close(file_desc);
}
