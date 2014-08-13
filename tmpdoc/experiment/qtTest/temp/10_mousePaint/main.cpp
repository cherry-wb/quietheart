/* 程序功能：
 * 使用鼠标在部件上面画线。
 * 缺点如果移动快了就成了虚线了。
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

