#include "myCallback.h"
#include <QPushButton>
#include <QApplication>
//#include <QThread>
#include <iostream>
using std::cout;
using std::endl;
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	button = new QPushButton(this);
	se = NULL;
	QObject::connect(button, SIGNAL(clicked()), this, SLOT(callback()));
}

void MyCallback::callback(void)
{//点击按钮
	//建立自定义事件
	if(se == NULL)
	{
		se = new UserEvent("my custom event");
	}
	//发送自定义事件
	//这个post函数必须处理在heap上面分配的，因为事件被处理之后就会delete了。
	//所以这个post函数只能第一次有用，之后就崩溃了。似乎是事件处理之后就被删除了。
	//QApplication::postEvent(this,se);
	//send函数可以多次反复处理不会出现多次处理就崩溃的现象。因为事件处理之后不会被删除。
	QApplication::sendEvent(this, se);
}
void MyCallback::customEvent(QEvent *e)
{
	if(e->type() == QEvent::User+1)
	{
		UserEvent *re = (UserEvent*)e;
		cout<<re->str().toLocal8Bit().data()<<endl;
	}
}
