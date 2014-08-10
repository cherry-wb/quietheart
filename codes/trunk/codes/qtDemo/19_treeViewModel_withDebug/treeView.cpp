/*程序功能： 一个简单的treeView部件的使用,本例实现的功能包括
 * 这个程序具有调试的标记。添加方法是：
 * qmake -project
 * 之后在生成的***.pro中添加：CONFIG += debug
 * 之后
 * qmake
 * make
 * 这样就可以用gdb调试了。
 * */
#include <QApplication>
#include "myCallback.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MyCallback *test = new MyCallback;
	test->show();
	test->setGeometry(100,100,100,100);

	int ret = app.exec();
	delete test;
	return ret;
}
