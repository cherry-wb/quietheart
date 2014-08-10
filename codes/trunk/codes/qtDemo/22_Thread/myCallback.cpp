#include <QPushButton>
#include <QTimer>
#include "myCallback.h"
#include <iostream>
using std::cout;
using std::endl;
void MyThread::run()
{//线程的主函数
	//QTimer::singleShot(1000, this, SLOT(myPrint()));//这样周期调用的话exit/quit无法停止
	QTimer timer;
	connect(&timer, SIGNAL(timeout()), this, SLOT(myPrint()));
	timer.start(1000);
	
	//////启动线程自己的事件循环
	//没有这句话，执行不到singleShot的槽,有了循环才能执行信号和槽的链接
	//另外QThread不能使用QWidget,文档说的。
	exec();
}
void MyThread::myPrint(void)
{
	//QTimer::singleShot(1000, this, SLOT(myPrint()));//这样就实现singleShot周期调用了
	static int i = 0;
	cout<<"print static i:";
	cout<<i++<<endl;
	cout<<", private j:"<<j++<<endl;//每个线程的数据不同
	if(j > 5)
	{//退出线程的循环
		cout<<"will quit"<<endl;
		exit(0);//退出消息循环
		//quit();
	}
}
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	t = NULL;
	btn = new QPushButton(this);
	QObject::connect(btn, SIGNAL(clicked()), this, SLOT(callback()));
}

void MyCallback::callback(void)
{
	cout<<"called callback!"<<endl;
	
	//启动线程
	//线程调用之后立即会发送一个started信号
	//结束之后会发送一个finished信号
	t = new MyThread(this);//必须新建立一个线程对象实现多线程否则还是单线程
	t->start();
}
