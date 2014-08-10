/*程序功能：
 *一种简单的在QObject中启动timer的方法。使用了timerEvent.
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
