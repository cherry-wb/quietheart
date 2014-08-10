#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QObject>
#include <QList>
#include <QPoint>
class MyCallback:public QObject
{
	Q_OBJECT
	public:
		MyCallback(QObject *parent = 0);
		QList<QPoint> listPoints;
	protected slots:
		void callback(void);
};
#endif
