#include "myCallback.h"

#include <QMouseEvent>
#include <QMutex>
#include <QtDebug>

int MyThread::j = 0;
QMutex MyThread::mutex_j;
void MyThread::run()
{
	//加锁lock()，如果其他进程再用这个mutex_j进行lock就会导致阻塞直至别人unlock
	//其他的锁操作：
	//tryLock()会立即返回，同时用返回值标记是加锁成功(true)或者失败(false)
	//tryLock (int timeout)，类似tryLock不过会等待一段时间
	mutex_j.lock();
	
	++j;
	qDebug()<<"In:"<<objectName()<<" Set j to "<<j;
	myPrint();
}
void MyThread::myPrint(void)
{
	int i = 0;
	while(++i<10000);
	qDebug()<<"In:"<<objectName()<<" Begin to print j";
	qDebug()<<"j is:"<<j;

	//解锁，这样之后其他对这个mutex_j进行lock操作的进程可以继续执行
	mutex_j.unlock();
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
	MyThread *t1 = new MyThread(this);
	t1->setObjectName("Thread1");
	t1->start();

	MyThread *t2 = new MyThread(this);
	t2->setObjectName("Thread2");
	t2->start();

	MyThread *t3 = new MyThread(this);
	t3->setObjectName("Thread3");
	t3->start();
}
