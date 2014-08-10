/* 程序功能：
 * 点击鼠标，弹出消息对话框，关闭对话框之后打印一个语句并关闭程序.
 * */
#include <QApplication>
#include "myCallback.h"
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	MyCallback mouseEvent;
	mouseEvent.show();

	return a.exec();
}

