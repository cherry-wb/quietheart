#ifndef __POPUPIM_H
#define __POPUPIM_H
#include <QWidget>
#include <QPushButton>

class PopupIM : public QWidget
{//输入法相关的类
    Q_OBJECT
public:
    PopupIM(QWidget *parent = NULL, const char *name = 0, Qt::WindowFlags flags = 0);
    ~PopupIM();

signals:
	//输入法相关的类的按键信号
    void keyPress( ushort unicode, ushort keycode,
	    ushort modifiers, bool press, bool repeat );
};

class PopupPushButton : public QPushButton
{//输入法界面键盘的一个按键
	//这个类的作用是负责把按钮的pressed转化为特定按键键盘的信号了类似QSignalMap
	Q_OBJECT
	public:
		PopupPushButton ( const QChar uni, ushort key, QWidget *parent )
			: QPushButton(parent), u(uni), k(key)
		{
			connect(this, SIGNAL(pressed()), this, SLOT(sendKeyForPress()));
			connect(this, SIGNAL(released()), this, SLOT(sendKeyForRelease()));
			setText(QChar(uni));
		}
		PopupPushButton ( const QString &text, ushort key, QWidget *parent )
			: QPushButton(parent), u(0xffff), k(key)
		{
			connect(this, SIGNAL(pressed()), this, SLOT(sendKeyForPress()));
			connect(this, SIGNAL(released()), this, SLOT(sendKeyForRelease()));
			setText(text);
		}
signals:
		//信号是发送出去的，所以一般发送给外部不会自己接受自己的信号
		void keyPress(ushort, ushort, ushort, bool, bool);

		private slots:
			void sendKeyForPress()
			{
				emit keyPress(u.unicode(), k, 0, TRUE, FALSE);
			}
		void sendKeyForRelease()
		{
			emit keyPress(u.unicode(), k, 0, FALSE, FALSE);
		}
	private:
		QChar u;
		ushort k;
};
#endif
