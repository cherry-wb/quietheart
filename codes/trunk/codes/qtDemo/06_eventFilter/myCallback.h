#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>

class QLineEdit;
class QEvent;
class QMouseEvent;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected:
		virtual bool eventFilter ( QObject * watched, QEvent * event );
		void mousePressEvent(QMouseEvent *);
	protected slots:
		void clicked();
	private:
	QLineEdit *line;
};
#endif
