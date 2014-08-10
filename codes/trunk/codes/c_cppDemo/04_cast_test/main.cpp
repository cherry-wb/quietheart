//程序功能：
//static_cast,dynamic_cast
//父子类之间的转换
//一个可能的输出结果如下：
//&b:0xbf91be28
//&d:0xbf91be20
//38pb:0xbf91be20
//40pb:0xbf91be20
//42pb:0xbf91be20
//47pd:0xbf91be28
//结论:父指针指向子对象地址，不用强转，即可。
//子指针指向父对象地址，只有static_cast可以编译通过。
#include <iostream>
using std::cout;
using std::endl;
class Base
{
	public:
	Base(){a1=1;}
	int a1;
};
class Derive:public Base
{
	public:
	Derive(){a2=2;}
	int a2;
};
int main(int argc, char *argv[])
{
	Base *pb;
	Derive *pd;
	Base b;
	Derive d;
	cout <<"&b:"<<&b<<endl;
	cout<<"&d:"<<&d<<endl;

	pb=&d;
	cout<<__LINE__<<"pb:"<<pb<<endl;
	pb=static_cast<Base*>(&d);
	cout<<__LINE__<<"pb:"<<pb<<endl;
	pb=dynamic_cast<Base*>(&d);
	cout<<__LINE__<<"pb:"<<pb<<endl;

	//pd=&b;//error
	//cout<<__LINE__<<"pd:"<<pd<<endl;
	pd=static_cast<Derive*>(&b);
	cout<<__LINE__<<"pd:"<<pd<<endl;
	//pd=dynamic_cast<Derive*>(&b);//error
	//cout<<__LINE__<<"pd:"<<pd<<endl;

	return 0;
}
