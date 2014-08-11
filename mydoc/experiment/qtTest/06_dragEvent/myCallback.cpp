#include "myCallback.h"

#include <QMouseEvent>
//#include <QDragMoveEvent>
#include <QtDebug>


MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	pressX = 0;
	releaseX = 0;
}
void MyCallback::clicked()
{
}
/*
void MyCallback::dragMoveEvent(QDragMoveEvent * event)
{
	qDebug()<<"@@@@@@@@@{"<<__PRETTY_FUNCTION__;
	qDebug()<<event->pos();
	if(releaseX-pressX>20)
	{
		qDebug()<<"drag!";
	}
	qDebug()<<"@@@@@@@@@}"<<__PRETTY_FUNCTION__;
}
*/
void MyCallback::mousePressEvent(QMouseEvent *e)
{
	qDebug()<<"@@@@@@@@@{"<<__PRETTY_FUNCTION__;
	pressX = e->pos().x();
	qDebug()<<"@@@@@@@@@}"<<__PRETTY_FUNCTION__;
}
void MyCallback::mouseReleaseEvent(QMouseEvent *e)
{
	qDebug()<<"@@@@@@@@@{"<<__PRETTY_FUNCTION__;
	releaseX = e->pos().x();
	if(releaseX-pressX>20)
	{
		qDebug()<<"drag!";
	}
	qDebug()<<"@@@@@@@@@}"<<__PRETTY_FUNCTION__;
}
