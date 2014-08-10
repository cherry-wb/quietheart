/*程序功能： 一个list列表部件,本例实现的功能包括
 * 为列表添加item（三种方法）
 * 给定位置获得item
 * 设置列表的选择模式（多选，单选）
 * 设置选择的相应的item会有相应的相应
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
