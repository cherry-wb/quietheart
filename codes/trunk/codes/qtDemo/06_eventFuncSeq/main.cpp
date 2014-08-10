/*程序功能：
 * 这个程序测试了event事件函数和一般函数之间调用次序的关系。
 * 每次点击产生resizeEvent事件，然后看log和代码。
 * 点击5次之后就会在resizeEvent循环中死循环不出来了。
 *
 * 测试结果：
 * 对于函数print1(),
 * 直接调用print1(),和QTimer::singleShot(0,this,SLOT(print1()))调用是不同的，
 * 前者立即被调用，后者需要等待下一个时间循环的时候（对应的下一个事件应该是timer）才调用。
 * 所以后者实际上并不是立即就起作用的。
 * 另外，类似moveEvent,showEvent,resizeEvent等也都是在实际发生了move,show,resize之后才被调用，
 * 而不是move,show,resize调用之后立即被调用，因为期间有一个事件循环等待的时间。
 * 这里，
 * 实际的结果不是想象的：
 * print3,print1,print2,
 * 也不是想象理论的：print2,print3,print1
 * 而是：print3,print2,print1
 * 这里，resizeEvent中的 print3竟然比立即调用的print2要快！并且如果resizeEvent不结束，
 * 就不会调用print2,也不会接受其他事件循环了。
 *
 * */
#include <QApplication>
#include "myCallback.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MyCallback my;
	my.show();

	return app.exec();
}
