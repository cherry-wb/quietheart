/*功能：
 *这个程序用来测试自旋锁
 *程序使用方法：
 *./test_spin <device_name> <major> <minor>
 *执行之后，会自动创建相应节点的device，然后进行读写，程序结束之后会删除相应节点.
*/
#include <stdio.h>

/*for atoi*/
#include <stdlib.h>

/*for mknod*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*for makedev*/
#include <sys/sysmacros.h>

int main(int argc, char *argv[])
{
	if(argc == 4)
	{
		/*make a char device node*/
		printf("make the device node:%s %d %d\n",argv[1],atoi(argv[2]),atoi(argv[3]));
		dev_t devno = makedev(atoi(argv[2]),atoi(argv[3]));
		mknod(argv[1], S_IRWXU |S_IFCHR, devno);
		
		/*open the char device node in parent at first!*/
		pid_t pid;
		int fd = 0;
		
		printf("open %s in parent\n",argv[1]);
		fd = open(argv[1],S_IRWXU);
		printf("the return value of open fd is:%d\n",fd);
		
		if((pid = fork()) < 0)
		{
			perror("Create child process error!\n");
			return 1;
		}
		else if(pid == 0)
		{/*child process*/
			printf("create the child process %ld!\n",getpid());
			/*open the char device node in child, will fail because spin lock and exit!*/
			printf("open %s in child\n",argv[1]);
			fd = open(argv[1],S_IRWXU);
			printf("child process exit with fd %d!\n", fd);
			return 1;
		}
		
		/*wait for the child to exit!*/
		waitpid(pid,NULL,0);
		printf("wait the exited child %ld and close fd in parent!\n",pid);
		/*close to release the opened device node.*/
		close(fd);
		
		/*open again the char device node, but will not fail,because have unlocked the spin lock.*/
		printf("open again the %s,in parent!\n",argv[1]);
		fd = open(argv[1],S_IRWXU);
		printf("the return value of open fd is:%d\n",fd);
	}
	else
	{
		printf("argument is not right.\n");
		printf("Usage:%s <device_name> <major> <minor>\n",argv[0]);
	}
}
