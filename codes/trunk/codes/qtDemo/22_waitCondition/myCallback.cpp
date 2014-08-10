#include "myCallback.h"

#include <QMouseEvent>
#include <QMutex>
#include <QWaitCondition>
#include <QtDebug>

int MyThread::j = 0;
QMutex MyThread::mutex_j;
QWaitCondition MyThread::wait_j;
void MyThread::run()
{
	if(objectName() == "WaitThread")
	{//等待j的值，当j大于等于5的时候才打印。另外一个线程用来修改j的值。
		qDebug()<<"In:"<<objectName()<<" wait j>=5 ";
		myPrint();
	}
	else if(objectName() == "ModifyThread")
	{
		while(1)
		{
			sleep(1);
			//mutex_j.lock();//对j的互斥锁
			++j;
			//mutex_j.unlock();//似乎如果仅仅为了同步，不用对它互斥了
			qDebug()<<"In:"<<objectName()<<" Set j to "<<j;
			if(j>=5)
			{
				break;
			}
		}
		//通知所有等待的进程条件满足了。
		//另外还有wakeOne()是随机通知一个等待的进程.
		//如果想要指定特定进程，需要分别定义wait_j条件信号。
		wait_j.wakeAll();
		//sleep(1);
		//j=0;
	}
	else
	{
		;
	}
}

void MyThread::myPrint(void)
{
	qDebug()<<"In:"<<objectName()<<"@@@@@@@@@{"<<__PRETTY_FUNCTION__;
	mutex_j.lock();

	//等待对j的同步条件,要求执行wait之前必须mutex_j加锁否则立即返回.
	//如果mutex_j是递归也立即返回。
	//执行wait的时候首先将mutex_j解开，然后等待其他进程调用wake以获得满足条件的信息，
	//然后再把mutex_j恢复到加锁的状态。
	//另外还有延迟等待，函数多个时间参数表示等待多久，具体看文档。
	wait_j.wait(&mutex_j);
	mutex_j.unlock();//这里使用互斥锁仅仅为了调用wait，并没有用到互斥访问。
	qDebug()<<"In:"<<objectName()<<" Begin to print j";
	qDebug()<<"j is:"<<j;
	j=0;
	qDebug()<<"In:"<<objectName()<<"@@@@@@@@@}"<<__PRETTY_FUNCTION__;
}

MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	;
}

void MyCallback::mousePressEvent(QMouseEvent *e)
{
	clicked();
	e->ignore();
}

void MyCallback::clicked()
{
	//t = new MyThread(this);
	MyThread *twait = new MyThread(this);
	twait->setObjectName("WaitThread");
	twait->start();

	MyThread *tmodify = new MyThread(this);
	tmodify->setObjectName("ModifyThread");
	tmodify->start();
}
