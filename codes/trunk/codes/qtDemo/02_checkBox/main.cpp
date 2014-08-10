/*程序功能：
 * 这是一个使用check box多选项目的例子。
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
