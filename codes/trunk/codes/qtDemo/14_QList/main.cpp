/* 程序功能：对QList数组的使用测试。包括：
 * 1）追加(可以插入)
 * 2）取出特定位置元素
 * 3）打印出元素数目
 * 4）打印(遍历)所有元素
 * 5）清除所有元素
 * 点击按钮调用自己定义的回调函数(槽)。
 * 注意，如果用一个类来初始化QList模板，那么最好模板类是一个指向这个类的指针，因为许多Qt类的拷贝构造函数是私有的，导致插入的时候会出错误。
 * 例如用：QList<QIcon*>，而不是QList<QIcon>
 * */
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include "myCallback.h"
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	QWidget window;
	window.show();

	MyCallback click_call;
	//指定按钮显示的文字,父窗口为window(0是它自己)
	QPushButton button( "Add_Clear", &window);

	//这里点击设置按钮则关闭程序
	QObject::connect(&button, SIGNAL(clicked()), &click_call, SLOT(callback()));
	button.show();

	return a.exec();
}

