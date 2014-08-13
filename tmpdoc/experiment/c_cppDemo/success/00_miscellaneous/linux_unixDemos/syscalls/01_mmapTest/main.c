//hello hello hello
/*程序功能：
 * 1)主要测试mmap和munmap的2)简单的write
 * 具体为：
 * 在命令中分别指定文件名，映射的长度，映射的起始地址.
 * 将文件映射到内存中
 * 把映射到内存中的内容用write写到标准输出。
 * 注意，这里没有对越界进行检测。
 * */
#include <sys/mman.h>//mmap
#include <unistd.h>//sysconf
#include <fcntl.h>//file open
#include <stdio.h>//printf
int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		write(STDOUT_FILENO,"hello\n",6);
		printf("usage:%s <filename> <offset> <length>\n",argv[0]);
		return 1;
	}
	char *filename = argv[1];//1)指定文件
	printf("the file to be mapped is:%s\n",filename);
	int fd = open(filename,O_RDONLY);

	int offset = atoi(argv[2]);//2)指定映射起始地址(页面的整数倍)
	printf("start offset of file to be mapped is:%d\n",offset);
	printf("page size is:%ld\n",sysconf(_SC_PAGE_SIZE));
	int realOffset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);//转换成页面的整数倍
	printf("real start offset of file to be mapped is:%d\n",realOffset);

	int length = atoi(argv[3]);//3)指定映射长度
	printf("the length to be map is:%d\n",length);
	int realLen = length+offset-realOffset;//实际写入的字节数
	printf("the real length to be map is:%d\n",realLen);

	//mmap的参数分别是：
	//NULL,让内核自己选择映射的地址;realLen指定映射的长度；
	//PROT_READ只读；MAP_PRIVATE不和其他的进程之间共享映射区域,数据也不写入对应的文件中；
	//realOffset映射文件的起始地址(页面的整数倍)。
	char *addr = mmap(NULL, realLen,PROT_READ,MAP_PRIVATE,fd,realOffset);//4)开始映射

	//关闭打开的文件，实际程序退出的时候会自动关闭。
	//关闭文件之后，相应的映射内存仍旧存在,映射的内存用munmap关闭。
	close(fd);
	//write的参数分别是：
	//STDOUT_FILENO:文件描述符号（这里是标准输出）
	//addr,将要写入文件的内容的地址
	//realLen,写入的长度,长度以addr作为起始地址
	write(STDOUT_FILENO,addr,realLen);//将映射的内容写到标准输出
	munmap(addr,realLen);//5)关闭映射的内存
	//write(STDOUT_FILENO,addr,realLen);//不能使用了
	printf("\n");
}
