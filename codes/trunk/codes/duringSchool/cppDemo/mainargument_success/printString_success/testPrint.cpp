#include<iostream>
using namespace std;
int main(int argc,char** argv)
{
	if(argc == 3)
	{
		cout<<0<<':'<<argv[0]<<endl;
		cout<<1<<':'<<argv[1]<<endl;
		cout<<2<<':'<<argv[2]<<endl;
	}
	else
		cout<<"error!"<<endl;
	return 0;
}