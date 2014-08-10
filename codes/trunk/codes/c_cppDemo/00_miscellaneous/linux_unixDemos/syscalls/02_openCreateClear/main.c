/*一个简单的使用open打开文件的例子。
 * int open(const char *pathname, int flags, mode_t mode);
 * 具体含义参见man。
 * 本程序是：
 * 如果文件不存在则新创建一个，存在则清零。打开的方式是用户读写执行。
 * */
//for open
#include <fcntl.h>

//for S_IRWXU
#include <sys/stat.h>
//#include <sys/types.h>
int main(int argc, char *argv[])
{
	//打开文件testFile,读写方式打开|如不存在则创建|打开的文件清零,权限0700
	int fd = open("./testFile",O_RDWR|O_CREAT|O_TRUNC,S_IRWXU);

	//向文件写入字符串
	write(fd,"hello\n",6);
	return 0;
}
