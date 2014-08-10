/*程序功能：一个自定义的菜单项
 * 这个程序使用两种方法实现自定义的action.
 * 第一个方法是利用QWidgetAction和一个自定义的QWidget来实现。
 * 第二个方法是自己继承QWidgetAction来实现。
 * */
#include <QApplication>
#include "myCallback.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MyCallback my;
	my.show();
	return app.exec();
}
