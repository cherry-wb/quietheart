#include <iostream>
using namespace std;
//自定义命名空间名字空间如果定义在main函数里面就出现了错误
namespace first
{
	char name = '1';
}
namespace second
{
	char name = '2';
}
char name = '3';
void main()
{	
	cout<<name<<endl;//如果没有char name = '3'会报错
	cout<<"开始测试命名空间"<<endl;
	cout<<first::name<<endl;
	cout<<second::name<<endl;
	using namespace first;
	//cout<<name<<endl;//这样显示名字冲突错误

	/*using namespace second;//不能这样了
	cout<<name<<endl;//这样引用就报错了只能如下引用second*/
	cout<<second::name<<endl;
	cout<<endl;
}