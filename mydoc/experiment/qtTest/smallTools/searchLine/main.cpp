/*程序的功能：
 * 一个简单的searchLine
 * 其中包括一个 lineEdit,一个search按钮，和一个clear按钮
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
