/*程序功能：便利passwd文件中所有的数据项，打印出相应的name，和uid
*#include <sys/types.h>
*#include <pwd.h> 
*struct passwd *getpwent(void); 
*函数getpwent如果运行失败了，返回NULL;成功之后返回一个passwd指针。
*返回的指针指向的是一个静态变量，每次调用其值都会被修改，每次调用getpwent都会返回下一条passwd记录。
*这个函数在第一次调用的时候会自动打开passwd文件，但是使用完了之后我们需要使用endpwent来关闭相应的文件。
*
*void setpwent(void);
*函数setpwent实现的是回滚功能，使用它之后，会回滚到第一个记录。getpwent会返回第一记录了。
*
*void endpwent(void);
*函数endpwent用来在使用完passwd之后关闭相应的文件。
*
*这三个函数不是posix中的，而是Single Unix Specification中的XSI定义的，一般的系统都支持这个功能。
*/
#include <stdio.h>
#include <pwd.h> 
int main(void)
{
	struct passwd  *ptr;
	setpwent();
	while ((ptr = getpwent()) != NULL)
	{
		printf("user id is:%d,user name is:%s\n",ptr->pw_uid,ptr->pw_name);
	}
	endpwent();
	return 0;
}
