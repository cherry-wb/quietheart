//#include <QMessageBox>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <iostream>
#include "myCallback.h"
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	right = 0;
	lineWidth = 3;
	windowSurface = NULL;
}

void MyCallback::mousePressEvent(QMouseEvent *e)
{
	if(pixmap.isNull())
	{
		//建立一个和当前窗口一样大小的pixmap
		pixmap = QPixmap(rect().size());
		//把当前窗口的背景填充到pixmap中，从pixmap的0,0开始填充
		pixmap.fill(this, 0,0);
	}
	points<<e->pos();
	if(e->button() == Qt::RightButton)
	{
		right = 1;
	}
	else
	{
		right = 0;
	}
}
void MyCallback::mouseReleaseEvent(QMouseEvent *e)
{
	points.clear();
}
void MyCallback::mouseMoveEvent(QMouseEvent *e)
{ 

	if(right == 1)
	{//用右键画
		if(points.size()>0)
		{
			points<<e->pos();

			//把内容先绘制到pixmap上面
			//防止刷新窗口的时候清除原来绘制的内容
			QPainter painter(&pixmap);//建立一个向pixmap上绘制的painter
			QPen pen;
			pen.setStyle(Qt::SolidLine);
			pen.setWidth(lineWidth);
			pen.setBrush(QColor(0,0,125,9));//透明色，这个程序快些绘制否则看不出
			pen.setCapStyle(Qt::RoundCap);
			pen.setJoinStyle(Qt::RoundJoin);
			painter.setPen(pen);
			painter.drawPolyline(points);

			//刷新的时候只将pixmap绘制到窗口上
			repaint();
		}

	}
	else
	{//用非右键画
		if(points.size()>0)
		{
			points<<e->pos();

			//把内容先绘制到pixmap上面
			//防止刷新窗口的时候清除原来绘制的内容
			QPainter painter(&pixmap);//建立一个向pixmap上绘制的painter
			QPen pen;
			pen.setStyle(Qt::SolidLine);
			pen.setWidth(lineWidth);
			pen.setBrush(Qt::yellow);
			pen.setCapStyle(Qt::RoundCap);
			pen.setJoinStyle(Qt::RoundJoin);
			painter.setPen(pen);
			painter.drawPolyline(points);

			//刷新的时候只将pixmap绘制到窗口上
			repaint();
		}
	}
}
void MyCallback::paintEvent( QPaintEvent * /*e*/ )
{
	QPainter painter(this);
	painter.drawPixmap(rect(),pixmap);
}
