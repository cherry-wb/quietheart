/* 程序功能：自定义槽，窗口内只有一个按钮，将按钮的click连接到自己的槽上。
 * 点击按钮调用自己定义的回调函数(槽)。
 * */
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include "myCallback.h"
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	QWidget window;
	window.show();

	MyCallback click_call;
	//指定按钮显示的文字,父窗口为window(0是它自己)
	QPushButton button( "Click!", &window);

	//这里点击设置按钮则关闭程序
	//这里，connect还有一个参数，指定连接的类型(如是否阻塞，排队等)，可以参考文档。
	//不同的连接类型导致信号和槽发送的时机也有所不同一般用默认就行了。
	QObject::connect(&button, SIGNAL(clicked()), &click_call, SLOT(callback()));
	button.show();

	return a.exec();
}

