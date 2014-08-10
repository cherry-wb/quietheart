#include "myCallback.h"
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QPushButton>
#include <iostream>
using std::cout;
using std::endl;
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout(this);
	///////类似桥梁的信号中转
	//即"发送者构件signal-->QSignalMapper的map槽(该槽发送信号mapped),
	//QsignalMapper的mapped信号--->接收者构件slot"
	QSignalMapper* mapper = new QSignalMapper(this);
	//接收的字符串类型消息通过（mapped）中转，连接到槽rcvStr上.
	connect(mapper, SIGNAL(mapped(const QString&)), this, SLOT(rcvStr(const QString&)));
	//接收的int类型消息通过（mapped）中转，连接到槽rcvInt上.
	connect(mapper, SIGNAL(mapped(int)), this, SLOT(rcvInt(int)));
	//还可以如下的映射：
	//void mapped ( QWidget * widget );
	//void mapped ( QObject * object );

	///////创建输入按钮
	//第一个点击按钮发送QString消息
	QPushButton* btn = new QPushButton("A",this);
	//这里设置发送者中转信号时发送一个"first is A"给mapper,
	//这样点击的click虽然没有参数但是却发送了一个"first is A",后面类似.
	//这个函数可以在以后修改映射的时候反复调用，只要mapper是同一个
	mapper->setMapping(btn, "first is A");
	//点击调用map槽（该槽发送mapped信号）
	connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));
	layout->addWidget(btn);

	//第一个点击按钮发送int消息
	btn = new QPushButton("1",this);
	//这里设置发送者中转信号时发送一个整数100给mapper,
	//这样点击的click虽然没有参数但是却发送了一个整数100.
	mapper->setMapping(btn, 100);
	//点击调用map槽（该槽发送mapped信号）
	connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));
	layout->addWidget(btn);
}

void MyCallback::rcvStr(const QString &str)
{
	cout<<"received QString is:"<<str.toLocal8Bit().data()<<endl;
}
void MyCallback::rcvInt(int in)
{
	cout<<"received int is:"<<in<<endl;
}
