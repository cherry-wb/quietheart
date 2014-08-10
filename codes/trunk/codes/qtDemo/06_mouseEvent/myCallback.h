#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H

//在这里声明不包含头文件可以使项目编译更快，头文件改动后减少重复编译
//在源文件中包含,但是理论这样实际上这样报错了，所以只能在头文件中包含了。
//class QMouseEvent;
//class QWidget;
#include <QWidget>
#include <QMouseEvent>

class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected:
		//按下（不是点击）鼠标会调用这个事件函数
		void mousePressEvent(QMouseEvent *);

		//释放鼠标按键调用这个事件函数
		void mouseReleaseEvent(QMouseEvent *);

		//双击鼠标执行这个事件函数
		void mouseDoubleClickEvent(QMouseEvent *);

		//移动鼠标调用这个事件函数
		void mouseMoveEvent(QMouseEvent *);

};
#endif
