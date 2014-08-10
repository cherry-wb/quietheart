#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
#include <QEvent>
class QString;
class QPushButton;

class UserEvent: public QEvent
{//用户自定义事件类
	public:
	//这里的事件id要大于QEvent::User，小于QEvent::MaxUser
	//registerEventType安全注册一个事件，防止重复，其参数是一个提示仅在可用时用，可为-1.
	//它返回事件id，必须强制转换为QEvent::Type
	UserEvent(QString s):QEvent((QEvent::Type)registerEventType(QEvent::User+1)), sz(s){;}
	QString str() const {return sz;}
	private:
	QString sz;
};
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
	//点击按钮的槽函数用来建立和提交自定义事件
		MyCallback(QWidget *parent = 0);
	protected:
	//这个函数会处理收到的自定义事件
	//当发生自定义的事件的时候自动会调用这个函数
		void customEvent(QEvent *e);
	protected slots:
		void callback(void);
	private:
	QPushButton *button;
	UserEvent *se;

};
#endif
