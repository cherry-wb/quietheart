/*程序功能：测试getopt选项以及选项的参数的处理函数的使用方法
 *
#include <unistd.h>
int getopt(int argc, const * const argv[], const
 char *options);
extern int optind, opterr, optopt;
extern char *optarg;

参数argc和argv和main函数的一样，它们就是main函数传进来的；
参数options是一个字符串，这个字符串包含命令支持的所有选项字符;

如果选项是非法的，或者选项缺少参数，那么getopt会返回一个'?'.
如果一个选项字符后面跟着一个冒号(即':')，那么说明这个选项需要一个参数。例如有一个命令如下：
	command [-i] [-u username] [-z] filename
那么这里的options应该赋值为："iu:z".
另外，getopt会忽略"--"后面的选项，例如:rm -- -bar,将删除-bar文件。

getopt支持的四个外部变量:
optarg:
如果一个选项需要参数，那么getopt在处理一个选项的时候把optarg设置成为指向选项参数字符串的指针。
opterr:
如果出现选项错误，getopt会打印一个错误消息。如果去掉这个特性，那么在程序中将opterr设置成0.
optind:
下一个要处理的参数在argv数组中的索引。它从1开始，在每次用getopt处理参数的时候会增1。
optopt:
如果在处理选项的时候遇到了一个错误，getopt将会设置optopt， 让它指向导致错误的选项字符串。
 * */
#include <unistd.h>
//#include <fcntl.h>//只用这个也行
//#include <getopt.h>//只用这个也行

#include <stdio.h>
extern char *optarg;
extern int optind;
int main(int argc, char *argv[])
{
	if(argc == 1)
	{//没有参数
		printf("Introduction:\n");
		printf("Syntax is:\n%s [-i] [-u username] [-z] filename\n",argv[0]);
	}
	else
	{
		printf("Begin to process...\n");
		char c;
		char *optStr = "iu:z";
		while((c = getopt(argc, argv, optStr)) != -1)
		{//不要忘了加"()","="的优先级小于"!=".
			switch(c)
			{//处理每一个选项
				case 'i':
					printf("The argument \'i\' is used. \n");
					break;
				case 'u':
					printf("The argument \'u\' is used,and ");
					printf("the parameter of \'u\' is:%s \n", optarg);//选项的参数
					break;
				case 'z':
					printf("The argument \'z\' is used. \n");
					break;
				case '?':
					printf("Invalid option!\n");
					break;

			}
		}

		//选项处理完毕之后，处理输入的真正参数
		printf("option ok, and the main parameter is \"%s\"\n", argv[optind]);
		printf("Processed complete!\n");
	}
	return 0;
}
