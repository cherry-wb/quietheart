/*功能：简单介绍c++中auto_ptr智能指针的使用。
*使用auto_ptr(智能指针)可以自动管理内存，防止手工管理时候内存泄露的问题。它实际就是一个类型。
*auto_ptr是一个模板类，这个类型的对象内部的析构函数完成对堆内存的释放，所以不要对这个对象的内存进行delete了。
*auto_ptr对象通过一个new出来的内存，以及指定好一个类型来初始化，而使用方法和指针一样。
*auto_ptr对象不要用于stl以及数组，它只适合管理堆内存中的单个元素。
*/
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::auto_ptr;
void my_func(void);
int main(int argc, char *argv[])
{
	my_func();
	return 0;
}

void my_func(void)
{
	//demo for manager heap memory by auto_ptr.
	auto_ptr<int> pInt(new int(0));
	*pInt = 2;
	cout<<*pInt<<endl;

	//demo for manager heap memory by hand.
	int *pInt2 = new int(2);
	cout<<*pInt2<<endl;
	delete pInt2;
}
