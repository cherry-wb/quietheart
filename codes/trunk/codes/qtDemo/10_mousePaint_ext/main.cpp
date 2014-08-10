/* 程序功能：流畅地使用鼠标在部件上面画线。
 * 如果直接绘制到窗口上面有如下问题：刷新窗口的时候会清空原有的内容。即：
 * 使用多边形的方式画线这就不会虚线，可是，
 * 松开鼠标时若清空多边形数据会导致再次绘制的时候清除原来的数据。
 * 解决方法是：
 * 绘制窗口的时候，不直接绘制到窗口中，而是先绘制到一个pixmap上，
 * 刷新的时候把pixmap绘制到窗口上。这样内容全在pixmap上保存着，不会因为刷新而清空原有内容了
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

