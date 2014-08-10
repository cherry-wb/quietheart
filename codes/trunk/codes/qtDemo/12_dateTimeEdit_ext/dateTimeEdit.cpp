/* 程序功能：窗口内有一个显示日期的编辑框，下面还有三个按钮。
 * 功能：
 * 设置日期显示的格式。
 * 点击按钮可以给相应的日期增加1??
 * 
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

