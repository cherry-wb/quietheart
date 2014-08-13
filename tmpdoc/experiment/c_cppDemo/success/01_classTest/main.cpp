/*程序功能：
 * 编写一个自己定义的类，然后调用它。
 * 注意编译的时候，需要指定多个文件。
 * 另外这里面有一个错误输出的测试
 * */
#include <iostream>
#include "myClass.h"
using std::cout;
using std::endl;
using std::cerr;
int main(int argc, char *argv[])
{
	cout<<"hello!"<<endl;
	MyClass my;
	cerr<<"this is the error output"<<endl;
	cout<<"ok!"<<endl;
	return 0;
}
