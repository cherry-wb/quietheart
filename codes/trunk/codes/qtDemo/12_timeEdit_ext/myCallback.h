#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
class QTimeEdit;
class QPushButton;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected slots:
		void callbackH(void);
		void callbackM(void);
		void callbackS(void);
	private:
		QTimeEdit *timeEdit;
		QPushButton *btnH;
		QPushButton *btnM;
		QPushButton *btnS;
		int h;
		int m;
		int s;
};
#endif
