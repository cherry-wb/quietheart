/*程序功能：建立一个可以有滚动条的构件，点击一下按钮就会增加一行QLabel,当随着QLabel数目的增加会出现滚动条。
 * 关键三点：
 * 1）调用QScroll::setWidget;设置滚动区域的widget
 * 2）调用QScroll::setWidgetResizable(true);自动调整widget大小
 * 3）需要在widget设置layout之后调用QScroolArda::setWWidget
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
