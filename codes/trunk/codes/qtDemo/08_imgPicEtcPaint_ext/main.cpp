/* 程序功能：绘制各种图像等
 *涉及的类有：QPixmap、QBitmap、QImage與QPicture等
 *分别使用这几个类绘制彩图（平台相关与无关），单色图，记录绘制动作与重放。
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

