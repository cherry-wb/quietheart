#include "myCallback.h"
#include <iostream>
#include <QDebug>
MyCallback::MyCallback(QObject *parent):QObject(parent)
{
	QObject::connect(this, SIGNAL(clickSignal()), this, SLOT(emitSignal()));
	qDebug()<<"@@@@@@@@@@"<<receivers(SIGNAL(clickSignal()));//判断这个信号被连接了多少次
}

void MyCallback::emitSignal(void)
{
	static int clickNumber = 1;//注意：静态局部变量在不同的对象中也是这一个。
	if(clickNumber & 1)
	{//如果奇数次点击，断开连接
		QObject::disconnect(this, SIGNAL(mySignal(int)), this, SLOT(callback(int)));
	}
	else
	{//如果偶数次点击则恢复连接
	//如果连接多次，那么点击一次就会发送多个信号
		QObject::connect(this, SIGNAL(mySignal(int)), this, SLOT(callback(int)));
	}
	clickNumber ^= 1;
	//发送信号
	emit mySignal(10);
}

void MyCallback::callback(int rcv)
{
	//获得发送信号的对象指针的例子：
	//QCheckBox *check = qobject_cast<QCheckBox *>(sender());

	using std::cout;
	using std::endl;
	cout<<"called callback!data is:"<<rcv<<endl;
}
