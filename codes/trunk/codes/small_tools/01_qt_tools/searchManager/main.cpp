/*程序功能：
 * 这里的例子是一系列check列表加上一个组合框。
 * 选择组合框和列表都会有响应，具体运行程序即可知道。
 * */
#include <QApplication>
#include "SearchManager.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	SearchManager my;
	my.show();
	app.exec();
	return 0;
}
