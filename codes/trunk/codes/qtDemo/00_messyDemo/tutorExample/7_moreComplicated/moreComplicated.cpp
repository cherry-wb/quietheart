/*程序功能：一个创建了许多构建的复杂的程序
 * 多个拖动滑块，每个滑块具有自己相应的显示构件显示自己的值
 * 通过拖动后一个滑块，会改变前一个的值。
 * 
 * 注意：
 * 如果把所有的东西都放在了一个独立的.cpp文件中，那么这个单文件程序编译不了。
 * 所以需要放在多个文件中去就没有问题了。
 *
 * 网上说的解决方法是：
 * I resolved this issue my running moc -o lcdrange.moc lcdrange.h, then editing lcdrange.cpp; commenting out the #include "lcdrange.h" and adding line #include "lcdrange.moc".
 * ???原因是qmake无法处理.cpp中的OBJECT宏。但是我还没有实践，
 * 后面7_morecomplicated2会实践这种情况。
 * */
#include <qapplication.h>
//#include "lcdRange.h"
#include "myWidget.h"

int main( int argc, char **argv )
{
	QApplication a( argc, argv );
	MyWidget w;
	a.setMainWidget( &w );
	w.show();
	return a.exec();
}

