#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>

class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected:
		void timerEvent(QTimerEvent *event);
	protected slots:
		void clicked();
	private:
};
#endif
