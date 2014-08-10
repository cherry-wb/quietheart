#include<iostream>
#include<ctype.h>
using namespace std;
int main(int argc,char** argv)
{
	if(argc == 3)
	{
		double a = atof(argv[1]);
		double b = atof(argv[2]);
		cout<<"the result is:"<<a+b<<endl;
	}
	else
	{
		cout<<"error!"<<endl;
		return 1;
	}
	return 0;
}