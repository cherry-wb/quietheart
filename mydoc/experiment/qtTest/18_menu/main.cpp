/* 程序功能：实现单级菜单，多级菜单，选择菜单，按钮菜单以及弹出菜单
 * 另外有添加分隔条，设置菜单激活状态
 * 主要步骤:
 * 1)建立一个QMenuBar
 * 2)建立将要实现的每个“菜单项”QAction
 * 3)建立菜单QMenu
 * 4)将菜单添加到QMenuBar中（或者添加到QMenu中）
 * 5)将菜单项添加到QMenu中
 *
 * 另外添加弹出菜单的步骤是：
 * 1)实现事件函数：
	void contextMenuEvent(QContextMenuEvent *event);
 * 2)构造函数中添加事先定义好的action（菜单项）：
 *  addAction(action3);//怀疑这一步多余
 * */
#include <QApplication>
#include "myCallback.h"
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	MyCallback test;
	test.show();
	return a.exec();
}

