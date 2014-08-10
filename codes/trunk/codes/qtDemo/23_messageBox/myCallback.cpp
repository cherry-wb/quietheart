#include <QMessageBox>
#include <QWidget>
#include <QMouseEvent>
#include <iostream>
#include "myCallback.h"
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	setMouseTracking(true);
}

void MyCallback::mousePressEvent(QMouseEvent *)
{ 
	QMessageBox::about( this, "Example","You haved pressed.\n");
	using std::cout;
	using std::endl;
	cout<<"after messagebox"<<endl;
	//这个函数关闭程序
	close();  
}
