#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QObject>
class MyCallback:public QObject
{
	Q_OBJECT
	public:
		MyCallback(QObject *parent = 0);
	signals:
		//这个信号函数只是信号作用，所以不能实现
		void clickSignal(void);
		void mySignal(int);
	protected slots:
		void emitSignal(void);
		void callback(int);
		//将button的标准click连接到这个clickSignal，然后它再用emit发送信号
};
#endif
