#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>

//class QDragMoveEvent;
class QMouseEvent;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected:
		void mousePressEvent(QMouseEvent *);
		void mouseReleaseEvent(QMouseEvent *);
//		void dragMoveEvent(QDragMoveEvent * event);
	protected slots:
		void clicked();
	private:
		int pressX;
		int releaseX;
};
#endif
