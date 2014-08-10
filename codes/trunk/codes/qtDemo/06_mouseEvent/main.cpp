/* 程序功能：
 * 1)点击鼠标，打印出鼠标的位置以及点击的按键
 * 2)双击鼠标，打印双击位置
 * 3)移动鼠标，显示移动并打印位置
 * 4)设置只有按住鼠标按键的时候才发送移动事件
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

