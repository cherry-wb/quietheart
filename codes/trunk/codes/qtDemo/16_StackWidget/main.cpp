/* 程序功能：
 * 三个标签添加到一个窗口中，同一时间只显示一个标签，点击按钮换标签。
 * 这个程序的功能和QStackedLayout类似
 * */
#include <QApplication>
#include "myCallback.h"
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	MyCallback stackWidget;
	stackWidget.show();

	return a.exec();
}

