#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
class QDateEdit;
class QPushButton;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected slots:
		void callbackD(void);
		void callbackM(void);
		void callbackY(void);
	private:
		QDateEdit *dateEdit;
		QPushButton *btnD;
		QPushButton *btnM;
		QPushButton *btnY;
		int d;
		int m;
		int y;
};
#endif
