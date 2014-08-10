#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
class QScrollArea;
class QVBoxLayout;
class QLabel;
class QPushButton;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected slots:
		void callback(void);
	private:
		QScrollArea *sa;
		QVBoxLayout *vbox;
		QWidget *saWidget;
		QPushButton *btn;
		int cnt;//已有label的数目
};
#endif
