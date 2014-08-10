#include "myCallback.h"

#include <QTimerEvent>
#include <QtDebug>


MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	timer1 = startTimer(500);//如果启动了，那么返回的timer非0
	timer2 = startTimer(1000);
	timer3 = startTimer(2000);
}
void MyCallback::clicked()
{
}
void MyCallback::timerEvent(QTimerEvent *event)
{
	static int tc1 = 0;
	static int tc2 = 0;
	static int tc3 = 0;
	qDebug() << "Timer ID:" << event->timerId();
	if(event->timerId() == timer1)
	{
		tc1++;
		if(tc1 == 5)
		{
			qDebug()<<"begin kill the timer.";
			killTimer(timer1);
		}
	}
	else if(event->timerId() == timer2)
	{
		tc2++;
		if(tc2 == 5)
		{
			qDebug()<<"begin kill the timer.";
			killTimer(timer2);
		}
	}
	else
	{
		tc3++;
		if(tc3 == 5)
		{
			qDebug()<<"begin kill the timer.";
			killTimer(timer3);
		}
	}
}
