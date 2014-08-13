/* 程序功能：窗口内有一排按钮每个按钮对应一个数字，最左边和最右面是箭头。
 * 点击箭头更新主窗口的按钮标签,类似输入法选择输入汉字时候的选择列表.
 * */
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include "myCallback.h"
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	MyCallback test;
	test.show();

	return a.exec();
}

