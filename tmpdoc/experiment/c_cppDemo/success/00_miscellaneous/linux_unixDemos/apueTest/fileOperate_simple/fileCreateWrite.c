/*程序功能：
 * 用各种方式打开一个文件，(只需要指定MY_FLAG和MY_MODE)
 * 本程序可以创建一个文件,然后写文件
 * */
#include<stdio.h>

/*for exit*/
#include <stdlib.h>

/*for open*/
#include<fcntl.h>

/*for write*/
#include <unistd.h>

/*bzero*/
#include <strings.h>

/*for strlen*/
#include <string.h>

#define MY_FLAG (O_CREAT | O_RDWR | O_NONBLOCK)
//#define MY_MODE (S_IRWXU | S_IRWXG | S_IRWXO)
#define MY_MODE (00700 | 00070 | 00007)
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("usage:%s filename\n",argv[0]);
	}
	else
	{
		int fd = -1;
		ssize_t count = 0;
		char buf[256] = {'\0'};/*初始化了就不用bzero了*/
		/*
		 *int open(const char *pathname, int flags, mode_t mode);
		 *1）pathname就是文件的路径，包括文件自身的名字
		 *2）
		 *"互斥"的flags是以下三者之一:
		 O_RDONLY,表示只读。
		 O_WRONLY,表示只写。
		 O_RDWR，表示读写。
		 *以下的flag值是可选的：
		 O_APPEND,每次写的时候添加到文件的最后。
		 O_CREAT,如果文件不存在将会创建文件。
		 O_EXCL,和O_CREAT一起指定，如果文件已经存在则open返回错误，具体看man。 
		 O_TRUNC，如果文件存在并且可写，那么把文件截断为0。
		 O_NOCTTY，如果pathname指定的是一个设备终端，那么不会把这个设备分配为进程的控制终端。
		 O_NONBLOCK或者O_NDELAY，用非阻塞的方式打开文件，这样open以及以后在这个文件描述符号上面的操作不会导致进程的等待了。
		 *3)mode是以下的值：
		 S_IRWXU,user具有读写执行权限00700
		 S_IRUSR,user具有读权限00400
		 S_IWUSR,user具有写权限
		 S_IXUSR,user具有执行权限
		 S_IRWXG,group具有读写执行权限00070
		 S_IRGRP，...
		 S_IWGRP,...
		 S_IXGRP,...
		 S_IRWXO,其他人具有读写执行权限00007
		 S_IROTH,...
		 S_IWOTH,...
		 S_IXOTH,...
		 这些值在O_CREAT指定的时候有用，否则将会被忽略。
		 * */
		if((fd = open(argv[1], MY_FLAG, MY_MODE)) == -1)
		{
			printf("error while open!\n");
			exit(1);
		}


		/*void bzero(void *s, size_t n);
		 *把s的前n个字节置0
		 * */
		//bzero(buf, sizeof(buf));
		sprintf(buf,"hello,this is content write to the file\nok!");
		/*ssize_t write(int fd, const void *buf, size_t count);*/
		if((count = write(fd, (char*)buf,strlen(buf))) == -1)
		{/*如果不用strlen而用256那么会写入许多空字符，显示为^@*/
			printf("error while write!\n");
			exit(1);
		}
		close(fd);
	}
	return 0;
}
