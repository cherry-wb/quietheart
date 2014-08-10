/*程序功能：一个创建了许多构建的复杂的程序
 * 将一个滑块，lcd显示构建，以及一个"绘制板"构建添加到grid中。
 * 拖动滑块，导致lcd显示构件显示自己的值
 * 同时，会更新绘制版上面显示的数字（绘制版有自己的背景色）,
 * 绘制板左下角的一个图形也相应旋转。
 * 相对于前面的第8个程序，这个程序只改变了cannon.cpp中的paintEvent
 * */
#include <qapplication.h>
#include "lcdRange.h"
#include "myWidget.h"

int main( int argc, char **argv )
{
	//诉Qt我们在这个程序中想使用一个不同的颜色分配策略,通常就使用默认得了。
	//QApplication::setColorSpec( QApplication::CustomColor );
	QApplication a( argc, argv );
	MyWidget w;
	a.setMainWidget( &w );
	w.show();
	return a.exec();
}

