/* 程序功能：窗口内有一个显示时间的编辑框，下面还有三个按钮。
 * 点击三个按钮，分别会给时间编辑框中的时／分／秒部分增1。
 * */
#include <QApplication>
#include "myCallback.h"
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	MyCallback test;
	test.show();
	return a.exec();
}

