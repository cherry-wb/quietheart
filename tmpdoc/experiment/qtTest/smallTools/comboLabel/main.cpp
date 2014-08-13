/*程序功能：使用label来模拟combo控件。
 * */
#include <QApplication>
#include "myCallback.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	EComboLabel my;
	my.show();
	app.exec();
	return 0;
}
