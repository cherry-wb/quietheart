/* 程序功能：自定义槽和信号，带参数具体如下：
 * 1)标准信号连接产生自定义信号：点击按钮，将clicked标准信号连接到自定义信号1中。
 * 2)连接信号：
 * 可在构造函数中连接信号：自定义信号1在构造函数中连接到自定义槽1上。
 * 如果点击偶数次，自定义信号2连接到自定义槽2上。
 * 3)断开信号:
 * 如果是奇数次，将自定义信号2和自定义槽2的连接断开.
 * 4)发射信号（带参数）:
 * 自定义槽1发送自定义信号2（带参数）。
 *
 * 偶数次的点击按钮最终调用自己定义的回调函数(槽),打印出传给槽的参数。
 * 另外，在构造函数里面打印一个log，判断连接了多少次这个信号。
 *
 * 注意：
 * 1）信号只能在类的头文件中声明，虽然它像函数，不能实现。
 * 2）如果将一个信号和槽连接n次了，那么发射一个该信号将执行槽n次。
 * 3）信号和槽的参数要匹配(只要槽的参数不多于信号应该也行)
 * 4) 信号返回类型是void
 *
 * 因为signal的作用是告诉其他对象本对象发生了什么事情，是一种通信机制，
 * 而event是告诉本对象本对象发生了什么事情,所以一般signal发送的时机是在处理event的时候发送，
 * 也因此signal一般是由定义它的那个类或者其子类发送的。
 * */
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include "myCallback.h"
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	QWidget window;
	window.show();

	MyCallback click_call;
	//指定按钮显示的文字,父窗口为window(0是它自己)
	QPushButton button( "Click!", &window);

	//这里点击设置按钮则关闭程序
	QObject::connect(&button, SIGNAL(clicked()), &click_call, SIGNAL(clickSignal()));
	button.show();

	return a.exec();
}

