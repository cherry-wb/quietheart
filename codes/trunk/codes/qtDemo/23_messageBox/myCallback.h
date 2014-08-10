#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H

#include <QWidget>
#include <QMouseEvent>

class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected:
		void mousePressEvent(QMouseEvent *);
};
#endif
