/*程序功能：一个捕获“拖拽”手势的程序。
 * 当拖拽大于20的时候松开鼠标会打印一个字符串。
 * 注意，当b截获a的事件，在b中处理来自a的事件event,event的pos还是相对于a的而不是b的。
 * */
#include <QApplication>
#include "myCallback.h"
int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	MyCallback my;
	my.show();
	return app.exec();
}
