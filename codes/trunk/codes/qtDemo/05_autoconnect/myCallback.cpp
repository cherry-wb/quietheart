#include "myCallback.h"
#include <QPushButton>
#include <QDebug>
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	mybutton = new QPushButton("hello",this);
	mybutton->setObjectName("mybutton");//设置对象名称
	QMetaObject::connectSlotsByName(this);//添加自动连接的特性
}

void MyCallback::on_mybutton_clicked()
{
	qDebug()<<"called callback!";
}
