#include "myCallback.h"
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QWidgetAction>
#include <QDebug>
#include <QStyleOptionMenuItem>
#include <QStylePainter>
#include <QRect>

MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	QPushButton *btn = new QPushButton("test",this);
	btn->show();
	resize(100,50);
	connect(btn,SIGNAL(clicked()),this,SLOT(callback()));

	popupMenu = new QMenu(this); 
	QAction *action1 = new QAction(tr("&New1"), this);
	QAction *action2 = new QAction(tr("&New2"), this);
	QAction *action3 = new QAction(tr("&New3"), this);
	QAction *action4 = new QAction(QIcon("./load.png"), tr("Bookstore"), this);
	/*
	MyMenuItem *item1 = new MyMenuItem(this);
	item1->setFixedSize(100,100);
	QWidgetAction *action1 = new QWidgetAction(popupMenu);
	action1->setDefaultWidget(item1);
	MyMenuItem *item2 = new MyMenuItem(this);
	QWidgetAction *action2 = new QWidgetAction(popupMenu);
	action2->setDefaultWidget(item2);
	MyMenuItem *item3 = new MyMenuItem(this);
	QWidgetAction *action3 = new QWidgetAction(popupMenu);
	action3->setDefaultWidget(item3);
	*/

	popupMenu->addAction(action1);
	popupMenu->addAction(action2);
	popupMenu->addAction(action3);

	//QStyleOptionMenuItem option;
	//option.menuRect = QRect(QPoint(0,0),QSize(200,300));
	//popupMenu->initStyleOption(&option,action4);


	//set style
	//popupMenu->setFixedSize(200,300);//这样只把菜单变大了，action还是那么小
	//popupMenu->setStyleSheet("QMenu::item { min-height: 100px }");//不管用？
	//popupMenu->setStyleSheet("QMenu::icon { min-height: 100px }");//不管用？
	//popupMenu->setStyleSheet("QMenu::item{background-color: transparent;}");//不管用？
	//popupMenu->setStyleSheet("QMenu::item{ height:100px; background-color: #000000;}");//不管用？
	//popupMenu->setStyleSheet("QMenu::indicator{ height:100px;}");//不管用？
	//popupMenu->setStyleSheet("QMenu::separator{ height:100px;}");//不管用？
	//popupMenu->setStyleSheet("QMenu::item:pressed{ height:100px; background:#000000}");//不管用？
	popupMenu->setStyleSheet("QMenu::item{ padding:100px;}");//设置菜单项的间距
}

void MyCallback::callback(void)
{
	popupMenu->exec();
	qDebug()<<"callback";
}
void MyCallback::paintEvent(QPaintEvent *e)
{
	//QStylePainter painter(popupMenu);
	//QStyleOptionMenuItem option;
	//option.menuRect = QRect(QPoint(20,20),QSize(200,300));
	//painter.drawPrimitive(QStyle::PE_FrameFocusRect, option);
}
