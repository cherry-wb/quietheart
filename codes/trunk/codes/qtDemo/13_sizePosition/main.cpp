/* 程序功能：控制控件的大小和位置,包括：
 * 顶层窗口的位置和大小。
 * 子窗口在父窗口的位置和大小。
 * */
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QDesktopWidget>
#include <QSize>
#include <iostream>
using std::cout;
using std::endl;
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	QWidget window;

	////////获得桌面大小参数的方法
	//QSize size;
	QSize size(320,240);
	QDesktopWidget* dw = QApplication::desktop();
	//获得可用屏幕数目
	cout<<"the number of available screens is :"<<dw->numScreens()<<endl;
	if(dw)
	{
		//获得整个（第0个）屏幕的大小(不含面板)
		size = dw->screenGeometry(0).size();
	}

	////////调整顶层窗口的大小和位置
	//将窗口移动到指定的位置
	window.move(0, size.height()>>1);
	//window.move(0, 0);
	//指定窗口的大小
	window.resize(size.width(), size.height()>>1);
	//window.resize(size.width(), size.height());//最大的大小不会被任务栏覆盖窗口

	////////调整子窗口的大小和位置(拖动改变父窗口大小后子窗口不自动调整)
	QPushButton button( "Click!", &window);
	//获取window大小，设置子构件大小
	QSize winSize = window.size();
	button.resize(winSize.width() >> 3, winSize.height() >> 3);
	//这里的位置是相对于父窗口的位置
	button.move(winSize.width() >> 1,winSize.height() >> 1);

	////////另外一种指定位置和大小的简单方法
	QPushButton button2( "Click2!", &window);
	//setGeometry传入的可以是一个矩形或者如下：
	//参数分别是矩形的位置和坐标
	button2.setGeometry(0,0,60,60);

	window.show();

	return a.exec();
}

