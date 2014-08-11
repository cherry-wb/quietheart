//程序功能：打印有颜色的字符串！这里只是在terminal中看，如果到了纯命令行界面，颜色有所变化。
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;

#define MY_BCOLOR_S "\033[1;34m"
#define MY_BCOLOR_E "\033[0m"

#define MY_RCOLOR_S "\033[1;31m"
#define MY_RCOLOR_E "\033[0m"

#define MY_YCOLOR_S "\033[1;32m"
#define MY_YCOLOR_E "\033[0m"

#define MY_GCOLOR_S "\033[1;39m"
#define MY_GCOLOR_E "\033[0m"
int main(int argc, char *argv[])
{
	printf("hello\n");//普通的颜色

	//稍微偏蓝
	printf( "\033[1;34mhello color!!!\n\033[0m ");//这样看有点不好阅读
	printf(MY_BCOLOR_S"Hello1 !!!\n"MY_BCOLOR_E);//使用c函数输出
	cout<<MY_BCOLOR_S<<"help!"<<endl<<MY_BCOLOR_E;//使用cpp的方式输出
	cout<<"nocolor"<<MY_BCOLOR_S<<"help!"<<MY_BCOLOR_E<<"nocolor"<<endl;//使用cpp的方式输出

	//红色
	printf(MY_RCOLOR_S"Hello red!!!\n"MY_RCOLOR_E);
	
	//黄色
	printf(MY_YCOLOR_S"Hello yellow !!!\n"MY_YCOLOR_E);
	
	//黄色
	printf(MY_GCOLOR_S"Hello green !!!\n"MY_GCOLOR_E);
}
