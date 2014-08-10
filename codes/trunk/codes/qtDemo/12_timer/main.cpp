/* 程序功能：
 * 程序实现定时调用的功能，用了两种计时方法：
 * 1）建立对象定时调用自定义函数
 * 2）利用QTimer的静态函数实现定时调用
 * */
#include <QApplication>
#include <QWidget>
#include <QTimer>
#include "myCallback.h"
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	QWidget window;
	window.show();

	MyCallback timer_call;

	//计时器
	QTimer *timer=new QTimer(&window);
	//设置超时信号的槽
	QObject::connect(timer, SIGNAL(timeout()), &timer_call, SLOT(callback()));
	//启动计时器
	//timer->setSingleShot(true);//这里设置只执行一次,默认flase
	timer->start(1000);
	//其他的计时器操作有：
	//int QTimer::timerId () const返回timer的id，如没有启动timer则-1
	//void QTimer::stop ()   [slot]
	//void QTimer::start ()   [slot]
	
	//另外一种简单计时调用的方法，不用QTimer对象了,好像只执行一次不会间隔执行
	QTimer::singleShot(6000, &a, SLOT(quit()));


	return a.exec();
}

