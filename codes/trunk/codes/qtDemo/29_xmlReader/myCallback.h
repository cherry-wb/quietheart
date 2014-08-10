#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>

class QMousePressEvent;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected:
		//void timerEvent(QTimerEvent *event);
		void mousePressEvent(QMouseEvent*);
	protected slots:
		void clicked();
	private:
};
#endif
