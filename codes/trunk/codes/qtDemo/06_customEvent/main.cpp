/*程序功能：自定义一个事件并且发送自定义的事件
 * 点击一个按钮将会建立一个自己定义的事件然后将这个事件发送出去并处理
 * */
#include <QApplication>
#include "myCallback.h"

int main(int argc, char *argv[])
{
	QApplication a(argc,argv);
	MyCallback my;
	my.show();
	return a.exec();
}
