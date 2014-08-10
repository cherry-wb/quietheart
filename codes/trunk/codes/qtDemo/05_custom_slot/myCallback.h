#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QObject>
class MyCallback:public QObject
{
	Q_OBJECT
	public:
		MyCallback(QObject *parent = 0);
	protected slots:
		void callback(void);
};
#endif
