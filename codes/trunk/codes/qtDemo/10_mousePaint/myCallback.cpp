//#include <QMessageBox>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <iostream>
#include "myCallback.h"
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
}

void MyCallback::mousePressEvent(QMouseEvent *e)
{
	startP.setX(e->x());
	startP.setY(e->y());
}
void MyCallback::mouseMoveEvent(QMouseEvent *e)
{ 
	endP.setX(e->x());
	endP.setY(e->y());
	//repaint();//这里会整体刷新导致一直只画一个点。
	//指定区域的重绘
	repaint(e->x(),e->y(),5,5);
	//setUpdatesEnabled(false);//使刷新无效

}
void MyCallback::paintEvent( QPaintEvent * /*e*/ )
{
	QPainter painter(this);

	//////用点画线（移动快了就成了虚线了）
	//painter.drawPoint(endP);
	
	//小线画线,这里快了也成了虚线了
	painter.drawLine(startP, endP);

	startP = endP;
}
