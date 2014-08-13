/*程序功能：测试获得指定用户名称或者用户id的passwd中的项
*#include <sys/types.h>
*#include <pwd.h>
*struct passwd *getpwuid(uid_t uid);
*struct passwd *getpwnam(const char *name);
*getpwuid在在ls将文件索引节点中的user id映射成为登录的用户名称的时候会被用到。
*getpwnam在我们输入用户名称时候login程序会用到。
*
*两个函数,如果运行失败了，返回NULL;成功之后都返回一个指向passwd结构的指针，
*这个指针内容是一个函数内部的静态变量，所以我们每次调用这两个函数的时候都会导致这个指针中的内容被后来的调用所覆盖。
*/
#include <stdio.h>
#include <pwd.h>
int main(void)
{
	struct passwd *test;

	//通过用户id获得passwd数据项
	test = getpwuid(0);
	printf("the name of 0 is:%s\n",test->pw_name);

	//通过指定用户名称，获得passwd数据项目
	test = getpwnam("root");
	printf("the uid of root is:%d\n",test->pw_uid);
	return 0;
}
