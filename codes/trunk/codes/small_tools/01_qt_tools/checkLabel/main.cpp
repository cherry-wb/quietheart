/*程序功能：自定义了一个check label,模拟QCheckBox的功能
 * */
#include <QApplication>
#include "myCallback.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QString test="test";
	ECheckLabel my(test);
	my.show();
	return app.exec();
}
