/*程序功能：自定义了一个可以点击的label,EPushLabel,然后用一个自定义的widget来使用EPushLabel.
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
