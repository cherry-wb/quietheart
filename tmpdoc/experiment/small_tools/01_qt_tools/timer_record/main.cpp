/*程序功能：
 *一个打点计时器。
 *功能包括：开始，打点，暂停，清除。
 *如果有bug，请联系：quiet_heart000@126.com
 * */

#include <QApplication>
#include "myCallback.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MyCallback my(0,Qt::WindowStaysOnTopHint);
	my.setGeometry(200,200,100,500);
	my.show();

	return app.exec();
}
