#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
class QLabel;
class QPushButton;
class QStackedWidget;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected slots:
		void showNext(void);
	private:
		QLabel *label1;
		QLabel *label2;
		QLabel *label3;
		QStackedWidget *sw;

		QPushButton *button;
};
#endif
