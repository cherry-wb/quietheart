/*本程序功能：获得用户进程以及用户的一些信息
 *
 * */
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>
int main(int argc,char **argv)
{
	/*相关定义*/
	pid_t my_pid,parent_pid;
	uid_t my_uid,my_euid;
	gid_t my_gid,my_egid;
	struct passwd *my_info;

	/*$$$$$$$$$$$关键调用$$$$$$$$$$*/
	my_pid=getpid();/*获得进程id*/
	parent_pid=getppid();/*获得父进程id*/
	my_uid=getuid();/*用户id*/
	my_euid=geteuid();/*有效用户id*/
	my_gid=getgid();/*组id*/
	my_egid=getegid();/*有效组id*/
	my_info=getpwuid(my_uid);/*其他信息*/
	/*
	 *struct passwd {
	 char *pw_name; // 登录名称 
	char *pw_passwd; // 登录口令 
	uid_t pw_uid; // 用户 ID 
	gid_t pw_gid; // 用户组 ID 
	char *pw_gecos; // 用户的真名 
	char *pw_dir; // 用户的目录
	char *pw_shell; // 用户的 SHELL
};
	 * */

	/*打印获取的信息*/
	printf("Process ID:%ld\n",my_pid);
	printf("Parent ID:%ld\n",parent_pid);
	printf("User ID:%ld\n",my_uid);
	printf("Effective User ID:%ld\n",my_euid);
	printf("Group ID:%ld\n",my_gid);
	printf("Effective Group ID:%ld\n",my_egid);
	if(my_info)
	{
		printf("My Login Name:%s\n" ,my_info->pw_name);
		printf("My Password :%s\n" ,my_info->pw_passwd);
		printf("My User ID :%ld\n",my_info->pw_uid);
		printf("My Group ID :%ld\n",my_info->pw_gid);
		printf("My Real Name:%s\n" ,my_info->pw_gecos);
		printf("My Home Dir :%s\n", my_info->pw_dir);
		printf("My Work Shell:%s\n", my_info->pw_shell);
	}
}
