//#include <QMessageBox>
#include <QWidget>
#include <QMouseEvent>
#include <iostream>
#include "myCallback.h"
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	//mousetracking是true时，不按button就可以产生mousemove消息(实践后按也行)
	//如果为false则需要按button才能产生mousemove消息
	//可以使用hasMouseTracking来判断它的值
	setMouseTracking(true);
}

void MyCallback::mousePressEvent(QMouseEvent *e)
{ 
	int x = e->x();
	int y = e->y();
	using std::cout;
	using std::endl;
	//Qt::NoButton
	//Qt::LeftButton
	//Qt::RightButton
	//Qt::MidButton
	//......
	if(e->button() == Qt::RightButton)
	{
		cout<<"right clicked at:"<<x<<","<<y<<endl;
	}
	else if(e->button() == Qt::LeftButton)
	{
		cout<<"left clicked at:"<<x<<","<<y<<endl;
	}
	else
	{
		cout<<"other clicked at:"<<x<<","<<y<<endl;
	}
}

void MyCallback::mouseReleaseEvent(QMouseEvent *e)
{ 
	int x = e->x();
	int y = e->y();
	using std::cout;
	using std::endl;
	if(e->button() == Qt::RightButton)
	{
		cout<<"right release at:"<<x<<","<<y<<endl;
	}
	else if(e->button() == Qt::LeftButton)
	{
		cout<<"left release at:"<<x<<","<<y<<endl;
	}
	else
	{
		cout<<"other release at:"<<x<<","<<y<<endl;
	}
	//QWidget::mouseReleaseEvent(e);
}

void MyCallback::mouseDoubleClickEvent(QMouseEvent *e)
{ 
	int x = e->x();
	int y = e->y();
	using std::cout;
	using std::endl;
	cout<<"mouse double click at:"<<x<<","<<y<<endl;
}

void MyCallback::mouseMoveEvent(QMouseEvent *e)
{ 
	int x = e->x();
	int y = e->y();
	using std::cout;
	using std::endl;
	cout<<"mouse move to:"<<x<<","<<y<<endl;
}


/*void MyCallback::mousePressEventSlot()
{
	using std::cout;
	using std::endl;
	cout<<"clicked at"<<endl;
	//给出一个提示信息
	QMessageBox::about( this, "Qt Mouse Click Event Example",
			"You haved clicked the prearranged position \nand the widget will be closed."
			);
	close();  //关闭程序
}
*/
