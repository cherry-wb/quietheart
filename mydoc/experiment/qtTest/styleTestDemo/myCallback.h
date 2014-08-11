#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
#include <QLabel>
class QMenu;
class QPaintEvent;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected:
		void paintEvent(QPaintEvent *);
	protected slots:
		void callback(void);
	private:
		QMenu *popupMenu;
};

class MyMenuItem:public QWidget
{
	Q_OBJECT
	public:
	MyMenuItem(QWidget *parent)
	{
		new QLabel("test",this);
	}
};
#endif
