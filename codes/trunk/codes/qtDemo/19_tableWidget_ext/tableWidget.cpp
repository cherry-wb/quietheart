/*程序功能： 一个Table列表部件,本例实现的功能包括
 * 为列表添加item(ok)
 * 给定位置获得item(ok)
 * 设置列表的选择模式（多选，单选）应该是设置TableWidgetItem的相关属性。
 * 设置选择的相应的item会有相应的相应(ok)
 * 注意：
 * 每个cell是可以编辑的。
 * */
#include <QApplication>
#include "myCallback.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MyCallback *test = new MyCallback;
	test->resize(320,200);
	test->show();

	int ret = app.exec();
	delete test;
	return ret;
}
