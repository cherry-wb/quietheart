/*程序功能:一个利用无名管道通信的程序
 * 这个程序利用无名管道进行通信,子进程用system调用一个外部命令echo,
 * 父进程等子进程成功返回并接收system运行的命令的输出,并存放在一个字符数组里面
 * 子进程命令的输出用文件符号重新定向来实现。
 * 注意，
 * 如果管道满的时候写或者管道空的时候读会导致阻塞。
 * 不需要的管道应该关闭。
 * */

/*这个函数用于执行一个shell命令，并把命令输出到指定字符串中
 *command：将要执行的命令
 *output：命令的输出
 *size：output的大小
 *如果函数失败则返回-1,成功返回输出的字符的数目。
 */
#include<stdio.h>

/*pid_t, STDOUT_FILENO*/
#include<unistd.h>

/*exit*/
#include<stdlib.h>

#define OUT_SIZE 256
int mysystem(const char *command, char *output, int size)
{
	int fd[2];
	pid_t pid;
	int status;
	int count;

	/*创建无名管道文件，返回两个文件描述服号对应fd的两个元素
	 * fd[0]是用于读取的文件描述符号，fd[1]是用于写入的文件描述符号*/
	pipe(fd);

	if((pid = fork()) < 0)
	{
		perror("create child error!\n");
		return -1;
	}
	else if(pid > 0)
	{/*父进程*/
		/*等待子进程的结束*/
		wait(&status);
		if(status < 0)
		{/*子进程返回值小于0代表出错*/
			perror("child run error!\n");
			return -1;
		}
		
		//父进程里不用的写文件描述符号(副本)，就关闭.man手册里也是这样做得
		close(fd[1]);
		if((count = read(fd[0], output, size)) < 0)
		{/*读取数据，数据来自子进程*/
			perror("read pipefile error!\n");
			//此处用close(fd[0])吗？
			return -1;
		}
		close(fd[0]);
		return count;
	}
	else
	{/*子进程*/
		//子进程里不用的写文件描述符号(副本)，就关闭.man手册里也是这样做得
		close(fd[0]);
		if(dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO)
		{/*这里把标准输出重定向到写文件描述符号，省得再write了*/
			perror("dup2 STDOUT_FILENO error!\n");
			//此处用close(fd[1])吗？
			exit(-1);
		}
		close(fd[1]);
		/*执行命令*/
		exit(system(command));
		/*用execl执行命令也行类似下面，但是下面的不行,
		 * -c选项是表示由字符串指定命令*/
		/*if(execl("/bin/sh", "-c", command, (char*)0) == -1)
		{//执行命令的时候
			//此处用close(fd[1])吗？
			exit(-1);
		}*/
	}
}

int main(int argc, char *argv[])
{
	char command[] = {"echo \"hello,unnamed pipe\""};
	char output[OUT_SIZE] = {'\0',};
	if(mysystem(command, output, OUT_SIZE - 1) == -1)
	{
		perror("excute mysystem failed!\n");
		return 1;
	}
	else
	{
		printf("The command is:\n%s\n", command);
		printf("The output of the command is:\n%s\n", output);
	}
	return 0;
}
