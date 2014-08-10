#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
#include <QList>
#include <QLabel>
#include <QMouseEvent>

class QMenu;
class EPushLabel;
class QStringList;
class EComboLabel:public QWidget
{
	Q_OBJECT
	public:
		EComboLabel(QWidget *parent = 0);
		void updateLayout();
		void addItem(QString);
	protected:
		//void timerEvent(QTimerEvent *event);
		void init();
	signals:
		void activated(const QString&);

	protected slots:
		void clicked();
		void activeItem();
	private:
	EPushLabel *titleLabel;
	EPushLabel *arrowLabel;
	QMenu *selectMenu;
	QList<QAction*> selectItems;
	QStringList itemTitles;
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
