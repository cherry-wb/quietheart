/*不同线程之间的串行化执行
 * QMutex确保了某些特殊的代码部分在多线程的时候会被串行地执行到.
 * QMutex确保某些代码段在同一个时刻只能由一个进程来执行它，最好用QMutexLocker。
 * QMutex是互斥访问的概念，虽然也能实现同步，和同步不太一样。
 * 本程序功能是：
 * 点击窗口的时候：
 * 程序建立了t1,t2,t3三个线程。
 * 三个线程所做的都是：
 * 1)修改变量j:++j.
 * 2)延迟一定时间
 * 3)打印变量j
 *
 * 期望的是,t1执行打印的时候j=1. t2执行打印的时候j=2. t3执行打印的时候j=3.
 * 如果没有QMutex的控制，那么将会在t1,t2,t3执行打印的时候都打印3。
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
