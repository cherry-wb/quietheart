#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class QSize;
class QFont;
class EPushLabel;
class ECheckLabel:public QWidget
{
	Q_OBJECT
	public:
		ECheckLabel(QString &text, QWidget *parent = 0, Qt::WindowFlags f = 0);
		void updateLayout();
		void setIconSize(const QSize &);
		void setFont(const QFont&);

		QString text();
		QFont font();
		int checkValue();
	signals:
		void stateChanged(int);

	protected slots:
		void checked();
	private:
		void init();
		//void mousePressEvent(QMouseEvent *event);
	
	private:
		EPushLabel *iconLabel;
		EPushLabel *textLabel;
		static const char * unChecked_xpm[];
		static const char * checked_xpm[];
		int isCheck;//now support 0 for unchecked and 1 for checked
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
		//void pressSignal(ClickLabel*);
		void pressSignal();
	protected:
		void mousePressEvent(QMouseEvent *event)
		{   
			if(rect().contains(event->pos())) { emit pressSignal(); }
		}   
};
#endif
