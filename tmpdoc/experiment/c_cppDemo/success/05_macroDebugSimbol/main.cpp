/*程序功能：
 * 测试一些方便的宏标记(实际是关键字不是宏)
 * __LINE__：当前行号
 * __FILE__：当前文件
 * __FUNCTION__：当前函数
 * __PRETTY_FUNCTION__：完整函数名，包括类信息和参数
 * __TIME__:当前时间
 * __DATE__:当前日期
 * 这些宏便于调试，都是编译器内置的。
 * __FILE__, __LINE__ 是ANSI C语言标准，各种C编译器都应当支持。
 * 而 __FUNCTION__ 是C99标准，故一些老的编译器就不支持。如gcc支持__FUNCTION__,而vc6就不支持。 
 *
 * 在gcc源码的./libcpp/init.c中定义了一些结构里面有相关的东西。
 * */
#include <iostream>
using std::cout;
using std::endl;
int main(int argc, char *argv[])
{
	cout<<"the line is:"<<__LINE__<<endl;//打印当前行
	cout<<"the file is:"<<__FILE__<<endl;//打印当前的文件名
	cout<<"the function is:"<<__FUNCTION__<<endl;//打印当前的函数名
	cout<<"the pretty function is:"<<__PRETTY_FUNCTION__<<endl;//打印完整的函数名和参数
	cout<<"the function is:"<<__TIME__<<endl;//打印当前的时间
	cout<<"the function is:"<<__DATE__<<endl;//打印当前的日期
	
	return 0;
}


