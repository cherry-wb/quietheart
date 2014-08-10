#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
class QPushButton;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected slots:
		//被自动连接的槽的声明格式：
		//void on_<object name>_<signal name>(<signal parameters>);
		void on_mybutton_clicked();

		private:
		QPushButton *mybutton;
};
#endif
