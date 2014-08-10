/* 程序功能：测试自动连接槽的机制。
 * 大致过程如下：
 * 1)声明被自动连接的槽的形式： void on_<object name>_<signal name>(<signal parameters>);
 * 这里，指定了发送信号的构建的objectName,以及对应的信号名及参数。
 * 2)自动连接则调用如下：QMetaObject::connectSlotsByName(this);
 * 添加这句话之后才能够自动连接。
 * */
#include <QApplication>
#include "myCallback.h"
int main( int argc, char **argv )
{
	QApplication a( argc, argv );
	MyCallback my;
	my.show();

	return a.exec();
}

