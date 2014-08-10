#include<iostream.h>
//宏定义开关可以改变，用于调试
#define DEBUGPREBUILD 1

void main()
{
	cout<<"开始测试！"<<endl;
#if	DEBUGPREBUILD ==1
	cout<<"这里是设置宏定义DEBUGPREBULD为1的时候"<<endl;
#else
	cout<<"这里是设置宏定义DEBUGPREBULD不为1的时候"<<endl;
#endif
	cout<<"总会执行到这里"<<endl;
}