/*程序功能：一个多线程程序的例子，没有设置同步机制。具体可以参见官方文档：
 * http://qt.nokia.com/doc/4.5/qthread.html#details
 * 具体实现的是：
 * 每次点击一个按钮都会启动一个线程并且执行，
 * 执行的内容是定时每一秒打印一个公共数字i++，和一个私有数字j++。
 * 每个线程执行5次就自动退出。
 *
 * 注意：线程想要链接外部信号到自己的槽则需要在run()主函数中运行exec()启动自己的事件循环。
 * */
#include <QApplication>
#include "myCallback.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MyCallback my;
	my.show();
	int status = app.exec();
	return status;
}
