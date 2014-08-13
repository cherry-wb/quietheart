/*
 *管道通信：有名管道
 *无名管道只能用于具有亲缘关系的进程之间，而有名管道可以在互不相关的两个进程间
 *实现彼此通信。要注意，FIFO严格按照先进先出的规则，对管道及FIFO的读总是从开始
 *处返回数据，对它们的写则把数据添加到末尾，不支持lseek等文件定位操作。
 *有名管道的创建使用mkfifo()。创建成功后就可以使用open、read、write这些函数了。
 *写管道部分:
 使用管道之后，会在系统中留下一个文件，重启之后不会消失.需要手动删除.
 *本程序功能，创建一个管道，向里面写数据，也就是发送。
 * */

#include <stdio.h>
#include <stdlib.h>

/*这三个文件用于open*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>
#include <unistd.h>
#include <errno.h>

/*特别注意写管道时，设置打开管道文件的格式必须为可写*/
#define OPENMODE (O_WRONLY | O_NONBLOCK)

int main(int argc, char **argv)
{

	if (argc != 2)
	{
		printf("Please send something\n");
		printf("usage:%s messageTobeSent\n", argv[0]);
		exit(0);
	}
	else
	{
		int fd;
		int nwrite;

		/*打开管道文件，可写非阻塞*/
		if((fd = open("myfifo", OPENMODE)) < 0)
		{
			perror("open");
			exit(1);
		}
		/*向管道写入数据，这里要用strlen，如果用sizeof，则只是4个字节的指针*/
		if ((nwrite = write(fd, argv[1], strlen(argv[1]))) < 0)
		{
			if (errno == EAGAIN)
			{
				printf("The FIFO has not been read yet.Please try later\n");
			}
		}
		else
		{
			printf("%s send(write) \'%s\' to FIFO\n",argv[0], argv[1]);
		}
	}


	return 0;
}
