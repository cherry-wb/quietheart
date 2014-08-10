#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H

#include <QWidget>
#include <QMouseEvent>

class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected:

		//程序启动，窗口部件刷新自己，或者改变大小就会调用这个事件函数
		//如果想要重绘，调用repaint或者update函数
		//绘图工作都应该在paintEvent中完成
		void paintEvent( QPaintEvent * );

};
#endif
