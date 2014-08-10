#include<iostream>
#include <cstdlib> 
using namespace std;
int main(int argc,char** argv[])
{
	cout<<"测试调用系统命令"<<endl;
	system("dir");
	return 0;
}