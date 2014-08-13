#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class QLineEdit;
class EPushLabel;
class MyCallback:public QWidget
{
	enum {ELINE_FIXHEIGHT=40};
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
		void updateLayout();
	protected:
		void init();
	protected slots:
		void clicked();
	private:
		QLineEdit *searchLine;
		EPushLabel *searchBtn;
		EPushLabel *clearBtn;
};
class EPushLabel:public QLabel
{
	Q_OBJECT
	public:
		EPushLabel(const QString &text, QWidget *parent = 0, Qt::WindowFlags f = 0)
			:QLabel(text, parent, f)
		{   
			;   
		}   
signals:
		void pressSignal();
	protected:
		void mousePressEvent(QMouseEvent *event)
		{   
			if(rect().contains(event->pos())) { emit pressSignal(); }
		}   
};
#endif
