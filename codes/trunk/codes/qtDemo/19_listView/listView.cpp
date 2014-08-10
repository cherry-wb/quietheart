/*程序功能： 一个简单的listView列表部件的使用,本例实现的功能包括
 * 点击listView中的表项，会做出相应的响应。
 * 一般给listView添加东西的步骤大致是：
 * 1）建立一个model,并设置model的显示方式（几行几列等等）
 * 2）为model添加item
 * 3）设置listView的model为刚才建立的model
 * 因为list使用model来显示，所以可以定制显示的自由度应该高一些了。
 * 有时候也可以继承一下listView
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
