#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
#include <QThread>

class QPushButton;
class MyThread: public QThread
{
	Q_OBJECT
	public:
	MyThread(QObject *parent = 0):QThread(parent){j = 0;}
	//这个函数是在执行start调用的时候执行，作为thread的"main"来运行。
	void run();
	protected slots:
		void myPrint(void);
	private:
		int j;
};
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected slots:
		void callback(void);
	private:
	QPushButton *btn;
	MyThread *t;
};
#endif
