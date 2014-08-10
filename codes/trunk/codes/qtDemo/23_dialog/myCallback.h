#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
#include <QDialog>
class QPushButton;
class MyDialog:public QDialog
{//定义一个dialog上面有两个button,否则上面什么都没有
	Q_OBJECT
	public:
		MyDialog(QWidget *parent = 0);
	protected slots:
		void acceptCallBack();
		void rejectCallBack();
	private:
		QPushButton *acceptBtn;
		QPushButton *rejectBtn;
};

class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected slots:
		void callback(void);
	private:
		QPushButton *btn;
};
#endif
