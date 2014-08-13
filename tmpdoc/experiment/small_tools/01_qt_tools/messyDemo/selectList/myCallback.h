#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
class QHBoxLayout;
class QPushButton;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected slots:
		void selBtn(const QString &);
	private:
	QHBoxLayout *hbox;
	QPushButton *lbtn;
	QPushButton *rbtn;

	QPushButton *btn1;
	QPushButton *btn2;
	QPushButton *btn3;
};
#endif
