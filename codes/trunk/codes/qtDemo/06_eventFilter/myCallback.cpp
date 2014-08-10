#include "myCallback.h"

#include <QLineEdit>
#include <QEvent>
#include <QtDebug>

MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	line = new QLineEdit(this);
	line->setObjectName(tr("myLineEdit"));

	//为line添加一个事件过滤,当line上面发生事件的时候，首先被事件过滤器对象处理。
	//具体是事件过滤对象中的eventFilter函数处理。
	line->installEventFilter(this);
}
void MyCallback::clicked()
{
}
bool MyCallback::eventFilter( QObject *obj, QEvent *e)
{
	//watched是被安装的对象，即调用installEventFilter安装本对象的对象。
	//event是截获的事件
	qDebug()<<"@@@@@@@@@"<<__PRETTY_FUNCTION__;
	qDebug()<<obj->objectName();
	qDebug()<<e->type();
	return false;//false表示处理完之后，继续默认的处理
}
void MyCallback::mousePressEvent(QMouseEvent *e)
{//不会在line之前调用？
	qDebug()<<"@@@@@@@@@"<<__PRETTY_FUNCTION__;
}
