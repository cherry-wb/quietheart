#include "myCallback.h"

#include <QResizeEvent>
#include <QTimer>
#include <QtDebug>

MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
}
void MyCallback::clicked()
{
	qDebug()<<"@@@@@@{"<<__PRETTY_FUNCTION__;
	qDebug()<<"orig geometry size is:"<<geometry();
	qDebug()<<"set size!";
	setFixedSize(QSize(geometry().width()+10,geometry().height()+10));
	qDebug()<<"after set size!";
	QTimer::singleShot(0,this,SLOT(print1()));
	print2();
	qDebug()<<"@@@@@@}"<<__PRETTY_FUNCTION__;
}
void MyCallback::resizeEvent(QResizeEvent*)//e
{
	qDebug()<<"@@@@@@{"<<__PRETTY_FUNCTION__;
	print3();
	qDebug()<<"@@@@@@}"<<__PRETTY_FUNCTION__;
}
void MyCallback::mousePressEvent(QMouseEvent*)//e
{
	clicked();
}
void MyCallback::print2()
{
	qDebug()<<"@@@@@@{"<<__PRETTY_FUNCTION__;
	qDebug()<<"call immediately after set size!";
	qDebug()<<"geometry size is:"<<geometry();
	qDebug()<<"@@@@@@}"<<__PRETTY_FUNCTION__;
}
void MyCallback::print1()
{
	qDebug()<<"@@@@@@{"<<__PRETTY_FUNCTION__;
	qDebug()<<"call by single shot  after set size!";
	qDebug()<<"geometry size is:"<<geometry();
	qDebug()<<"@@@@@@}"<<__PRETTY_FUNCTION__;
}
void MyCallback::print3()
{
	static int flag = 0;
	qDebug()<<"@@@@@@{"<<__PRETTY_FUNCTION__;
	qDebug()<<"geometry size is:"<<geometry();
	if(flag > 5)
		while(1);
	flag++;
	qDebug()<<"@@@@@@}"<<__PRETTY_FUNCTION__;
}
