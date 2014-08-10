#include <QScrollArea>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <iostream>
#include "myCallback.h"

using std::cout;
using std::endl;
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	//////全局的vbox布局，将添加一个scrollarea和一个pushbutton
	QVBoxLayout *gvbox = new QVBoxLayout(this);

	//////scrollarea以及其vbox布局
	sa = new QScrollArea;//scrollarea
	//这句话会使添加label的时候widget自动调整大小，添加多了会产生滚动条
	//如果没有则添加label的时候需要自己调整widget的大小。
	sa->setWidgetResizable(true);
	saWidget = new QWidget;//scrollarea内部的widget
	vbox = new QVBoxLayout(saWidget);//widget的layout
	QLabel *label = new QLabel("test");//先添加一个label
	vbox->addWidget(label);
	//这句话设置scrollarea中的widget，这句话必须在添加setLayout之后被调用否则看不见
	sa->setWidget(saWidget);
	saWidget->show();//实际没调用也能显示但是最好这样做文档说的。
	gvbox->addWidget(sa);
	
	//////pushButton
	btn = new QPushButton("addLabel");
	QObject::connect(btn, SIGNAL(clicked()), this, SLOT(callback()));
	gvbox->addWidget(btn);

	cnt = 1;
}

void MyCallback::callback(void)
{
	cout<<"add label!"<<endl;
	//setWidgetResizable为false或者没有它的调用的时候通过这里设置合适的大小以容纳label
	//saWidget->resize(saWidget->width(),saWidget->height() + saWidget->height()/cnt);
	++cnt;
	QLabel *label = new QLabel("test");
	vbox->addWidget(label);

}
