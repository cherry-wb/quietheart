//功能：本程序测试const_cast的功能。
//该运算符用来修改类型的const或volatile属性。除了const或volatile修饰之外，type_id和expression的类型是一样的。
//常量指针被转化成非常量指针，并且仍然指向原来的对象；
//常量引用被转换成非常量引用，并且仍然指向原来的对象；常量对象被转换成非常量对象。
//Voiatile和const类试。
//结论：
//这里，结果输出参见每行代码相应的注释。根据结果可知：凡是对结构体或类进行这个转换，都是成功的，但对char，short等基本>类型的转换，通过直接打印变量显示其值都是不成功的，但是通过指针却能显示出修改之后的值。
//通过对代码进行反汇编，可知，虽然本身我们没有使用优化，但系统还是对ic这个const进行了预编译般的替换，将它替换成“64h”（
//十六进制的64就是十进制的100），这肯定不是一般用户想要的结果，如果它不是一个C++的规范，应该算是个C++的bug吧。

#include <iostream>
using std::cout;
using std::endl;

class CTest
{   
	public:
		CTest(int i){m_val = i;cout<<"construction"<<m_val<<endl;}
		~CTest(){cout<<"destructionn"<<endl;}
		void SelfAdd(){m_val++;};
		int m_val;
};

int main(int argc, char *argv[])
{
	const int ic = 100;
	//int cc = const_cast<int>(ic);//编译错误
	int cc = const_cast<int&>(ic);
	cout<<cc<<endl;//输出100
	//const_cast<int &>(&ic)=200;//编译错误，从类型 ‘const int*’ 到类型 ‘int&’ 中的 const_cast 无效
	const_cast<int &>(ic)=200;
	cout<<ic<<endl;//输出100
	cout<<*(&ic)<<endl;//输出100
	//int *pc = &ic;//编译错误，从类型 ‘const int*’ 到类型 ‘int*’ 的转换无效
	const int *pc=&ic;
	//const_cast<int &>(pc)=200;//编译错误，从类型 ‘const int**’ 到类型 ‘int*’ 中的 const_cast 无效
	const_cast<int &>(ic)=200;
	//printf("%d,%d/n", ic, *pc);
	cout<<ic<<','<<*pc<<endl;//100,200
	//int *ppc = const_cast<int*>(ic);//编译错误
	int *ppc = const_cast<int*>(&ic);
	*ppc = 300;
	cout<<ic<<','<<*ppc<<endl;//100,300

	const CTest test(1000);
	CTest test2(1050);
	//test = test2;//编译错误，无法给常量赋值
	const_cast<CTest &>(test)= test2;
	cout<<test.m_val<<endl;//输出1050
}
