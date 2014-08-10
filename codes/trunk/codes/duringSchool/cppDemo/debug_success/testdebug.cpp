#include <iostream.h>
void main()
{
	cout<<"测试调试中的set next state"<<endl;
	int i = 0;
	cout<<"重新设置调试指针"<<endl;
	//int j = 2;
	int j = 3;//在此处改变j再重新设置调试指针
	i = i + j;
	cout<<i<<endl;
}