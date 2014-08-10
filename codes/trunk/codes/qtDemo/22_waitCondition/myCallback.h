#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
#include <QThread>

class QMutex;
class QWaitCondition;
class MyThread: public QThread
{
	Q_OBJECT
	public:
	MyThread(QObject *parent = 0):QThread(parent){}
	void run();
	protected slots:
		void myPrint(void);
	private:
		static int j;

		//对j的相关代码串行化的锁信号量
		//默认初始化为：RecursionMode mode = NonRecursive（非递归锁）
		//如果想要递归加锁，需要QMutex::Recursive.
		static QMutex mutex_j;
		static QWaitCondition wait_j;
};

class QMouseEvent;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected:
		virtual void mousePressEvent(QMouseEvent *e);
	protected slots:
		void clicked();
	private:
};
#endif
