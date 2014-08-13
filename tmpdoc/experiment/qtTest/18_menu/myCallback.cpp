#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <QPushButton>
#include <QContextMenuEvent>
#include <iostream>
#include "myCallback.h"
using std::cout;
using std::endl;
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	//菜单条
	menuBar = new QMenuBar(this);
	
	//先设置好"菜单项"
	action1 = new QAction(tr("&New1"), this);//题目
	action1->setIcon(QIcon("./test.jpg"));//图标
	action1->setShortcut(tr("Ctrl+N"));//快捷键
	action1->setToolTip("action1");//弹出提示,不管用?
	action1->setStatusTip(tr("action1"));//状态兰提示
	connect(action1, SIGNAL(triggered()), this, SLOT(do1()));//为菜单项连接动作

	action2 = new QAction(tr("&New2"), this);
	action2->setIcon(QIcon("./test.jpg"));
	action2->setShortcut(tr("Ctrl+M"));
	action1->setToolTip(tr("action2"));
	action2->setStatusTip(tr("action2"));
	action2->setCheckable(true);//设置为选项菜单，默认false
	action2->setEnabled(false);//设置为未激活菜单，默认true
	connect(action2, SIGNAL(triggered()),this,SLOT(do2()));

	//这里如果菜单项action3被选中则action2就激活
	action3 = new QAction(tr("&New3"), this);
	action3->setIcon(QIcon("./test.jpg"));
	action3->setShortcut(tr("Ctrl+P"));
	action1->setToolTip(tr("action2"));
	action3->setStatusTip(tr("action3"));
	action3->setCheckable(true);//设置为选项菜单，默认false
	//connect(action3, SIGNAL(triggered()), this, SLOT(do3()));
	connect(action3, SIGNAL(toggled(bool)),this,SLOT(isChecked(bool)));//选项曹

	//单级菜单
	singleMenu = menuBar->addMenu("Single");
	singleMenu->addAction(action1);
	singleMenu->addAction(action2);
	singleMenu->addAction(action3);

	//分隔线(这里没有看出什么啊?)
	menuBar->addSeparator();

	//多级菜单
	multiMenu = menuBar->addMenu("Multi");
	//建立子菜单1
	subMenu1 = multiMenu->addMenu("sub1");
	subMenu1->addAction(action1);
	subMenu1->addAction(action2);
	//分隔线
	multiMenu->addSeparator();
	//建立子菜单2
	subMenu2 = multiMenu->addMenu("sub2");
	subMenu2->addAction(action3);

	//按钮(带菜单的按钮)
	btn = new QPushButton("button",this);
	btn->move(50,50);//移动一下，防止挡住菜单
	btn->setMenu(subMenu1);//给按钮添加菜单（同时按钮上面会有一个箭头）

	//添加弹出菜单(这个函数没有看出来它有什么作用,注释掉了也没有什么变化)
	addAction(action3);
}
void MyCallback::do1(void)
{
	cout<<"action1"<<endl;
}
void MyCallback::do2(void)
{
	cout<<"action2"<<endl;
	//检测单选在单状态，选中则为checked
	if(action2->isChecked())
	{
		cout<<"action2 is checked"<<endl;
	}
	else
	{
		cout<<"action2 isn't checked"<<endl;
	}
}
void MyCallback::do3(void)
{
	cout<<"action3"<<endl;
}
void MyCallback::isChecked(bool flag)
{
	action2->setEnabled(flag);
	if(flag)
	{
		cout<<"is checked"<<endl;
	}
	else
	{
		cout<<"isn't checked"<<endl;
	}
}
void MyCallback::contextMenuEvent(QContextMenuEvent *event)
{
	if(event->reason() == QContextMenuEvent::Mouse)
	{//鼠标右键弹出菜单
		QMenu popupMenu; 
		popupMenu.addAction(action3);
		//popupMenu.move(event->x(),event->y());//这里不能用相对坐标因为位置不对
		popupMenu.move(event->globalX(),event->globalY());
		popupMenu.exec();
		//popupMenu.exec(event->globalPos());
		//popupMenu.popup(event->globalPos());
	}
	else
	{//例如按windows键盘中的菜单按键
		cout<<"other reason!"<<endl;
	}
}
