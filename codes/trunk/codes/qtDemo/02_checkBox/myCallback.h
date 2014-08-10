#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>

class QCheckBox;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected:
	protected slots:
		//state of checkbox changed
		void stateChanged(int);
	private:
	QCheckBox *check1;
	QCheckBox *check2;
	QCheckBox *check3;
};
#endif
