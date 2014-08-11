#include "myCallback.h"

#include <QTimerEvent>
#include <QtDebug>


MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	startTimer(500);
	startTimer(1000);
	startTimer(2000);
}
void MyCallback::clicked()
{
}
void MyCallback::timerEvent(QTimerEvent *event)
{
	static int timer1 = 0;
	static int timer2 = 0;
	static int timer3 = 0;
	qDebug() << "Timer ID:" << event->timerId();
}
