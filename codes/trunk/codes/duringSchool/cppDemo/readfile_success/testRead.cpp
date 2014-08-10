#include<iostream>
#include<fstream>
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
/*using namespace std;*/
int main(void)
{
	char filename[256];
	cout<<"请输入文件名(包含扩展名的txt文件):"<<endl;
	cin>>filename;
	ifstream infile;
	infile.open(filename);
	while(!infile.is_open())
	//while(!infile)也可以
	{
		cout<<"文件不存在！请重新输入！"<<endl;
		cin>>filename;
		infile.clear();
		infile.open(filename);	
	}
	char c = ' ';
	c = infile.get();
	while(!infile.eof())
	{
		cout<<c;
		c = infile.get();				
	}
	infile.close();
	return 0;
}