#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>

class QResizeEvent;
class QMouseEvent;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected:
		void resizeEvent(QResizeEvent *e);
		void mousePressEvent(QMouseEvent *e);
	protected slots:
		void clicked();
		void print1();
	private:
		void print2();
		void print3();

};
#endif
