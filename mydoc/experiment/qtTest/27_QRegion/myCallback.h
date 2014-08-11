#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected slots:
		void callback(void);
};
#endif
