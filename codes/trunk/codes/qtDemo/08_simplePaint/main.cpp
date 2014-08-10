/* 程序功能：绘制基本的图形
 * 1)矩形，椭圆,填充以上图形
 * 2)点，直线，弧线
 * 3)文字
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

