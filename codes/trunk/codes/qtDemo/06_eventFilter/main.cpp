/*测试事件过滤：
 * 本程序主窗口中有一个lineedit对象，
 * 设置lineedit对象的事件首先被主窗口"截获"处理。
 *
 * event filter,给一个对象a安装了一个eventfileter对象b，
 * 那么到达a对象的事件会首先被b处理，之后再决定由a处理与否。
//void installEventFilter ( QObject * filterObj )
//virtual bool eventFilter ( QObject * watched, QEvent * event )
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
