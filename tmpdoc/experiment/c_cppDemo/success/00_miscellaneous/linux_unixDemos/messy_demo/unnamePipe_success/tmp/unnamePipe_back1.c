/*程序功能:一个利用无名管道通信的程序
 * 这个程序利用无名管道进行通信,子进程用system调用一个外部命令,
 * 父进程接收system运行的这个命令的输出,并存放在一个字符数组里面
 *
 * 注意，
 * 如果管道满的时候写或者管道空的时候读会导致阻塞。
 * 不需要的管道应该关闭。
 * */
#include<stdio.h>
#include<unistd.h>
#include<string.h>
/*定义接受到的消息的长度*/
#define MSGLEN 255

int main(int argc, char *argv[])
{
	/*无名管道的文件标识符号,*/
	int fd[2];

	/*count是已经读的字节数,n是当前读了多少字节*/
	int count, n;
	char *buf[MSGLEN];
	pid_t pid;

	/*把接受/发送消息缓冲区设置为0*/
	memset(buf, 0, MSGLEN);

	if(pipe(fd) < 0)
	{
		perror("make pipe failed!\n");
		return -1;
	}

	/*创建子进程*/
	if((pid = fork()) < 0 )
	{
		perror("make child process failed!\n");
		return -1;
	}
	else if(pid > 0)
	{/*父进程接收消息*/
		/*首先关闭写*/
		close(fd[1]);
		count = 0;
		while((n = read(fd[0], buf + count, MSGLEN)) > 0 && count < MSGLEN)
		{
			count += n;
		}
		printf("receive from child is:%s\n", buf);
	}
	else
	{/*子进程发送消息*/
		close(fd[0]);
		if(fd[1] != STDOUT_FILENO)
		{
			if(dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO)
			{
				perror("dup file failed\n");
				return -1;
			}
		}
		system("echo good");//实际没有必要用system，用exec就行
	}

	return 0;
}
