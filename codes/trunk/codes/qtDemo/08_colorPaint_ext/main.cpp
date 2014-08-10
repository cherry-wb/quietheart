/* 程序功能：绘制彩色的图形
 * 1)彩色的具有一定属性的矩形和线
 * 2)彩色的填充和文字
 * 3)图像
 * */
#include <QApplication>
#include "myCallback.h"
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	MyCallback my_paint;
	my_paint.show();
	return a.exec();
}

