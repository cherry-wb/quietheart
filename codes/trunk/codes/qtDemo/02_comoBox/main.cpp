/*程序功能：
 * 这个例子是一个使用QCombo下拉列表框的使用举例。
 * */
#include <QApplication>
#include "myCallback.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MyCallback my;
	my.show();
	app.exec();
	return 0;
}
