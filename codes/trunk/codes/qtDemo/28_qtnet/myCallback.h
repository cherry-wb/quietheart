#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>

class QNetworkAccessManager;
class QNetworkReply;
class QLineEdit;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected:
	protected slots:
		void clicked();
		void finished(QNetworkReply*);
	private:
		QLineEdit *lineUrl;
		QNetworkAccessManager *manager;
};
#endif
