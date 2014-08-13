/*功能：本程序实现在程序中的重定向操作，这里把标准输出重新定向为了一个文件中。*/
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define BUFFER_SIZE 1024
int main(int argc,char **argv)
{
	int fd;
	char buffer[BUFFER_SIZE];
	if(argc!=2)
	{
		fprintf(stderr,"Usage:%s outfilename\n\a",argv[0]);
		exit(1);
	}
	if((fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR))==-1)
	{/*首先打开文件*/
		fprintf(stderr,"Open %s Error:%s\n\a",argv[1],strerror(errno));
		exit(1);
	}
	if(dup2(fd,STDOUT_FILENO)==-1)
	{/*将标准输出重定向到fd文件描述符号上面*/
		fprintf(stderr,"Redirect Standard Out Error:%s\n\a",strerror(errno));
		exit(1);
	}
	fprintf(stderr,"Now,begin to test:\n");/*因为标准输出被重新定向了，所以用标准错误来输出提示信息*/

	printf("this string is from standard oupput\n");/*这里本应该在标准输出的信息却打印到了文件中，因为重定向了*/
	/*close(fd);这一步是需要的吗？？例子里没有给出*/
	exit(0);
}
