/*程序功能：建立一个dialog模式对话框，弹出对话框并阻塞当前调用，然后退出返回输入选择的按钮。
 *
 * */
#include <QApplication>
#include <QWidget>

#include <iostream>
#include "myCallback.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QWidget window;

	MyCallback my(&window);
	window.show();

	app.exec();
	return 0;
}
