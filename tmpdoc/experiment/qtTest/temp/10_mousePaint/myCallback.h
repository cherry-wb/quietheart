#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H

//在这里声明不包含头文件可以使项目编译更快，头文件改动后减少重复编译
//在源文件中包含,但是理论这样实际上这样报错了，所以只能在头文件中包含了。
//class QMouseEvent;
//class QWidget;
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected:
		//按下（不是点击）鼠标会调用这个事件函数
		void mousePressEvent(QMouseEvent *);

		//释放鼠标按键调用这个事件函数
		//void mouseReleaseEvent(QMouseEvent *);

		//双击鼠标执行这个事件函数
		//void mouseDoubleClickEvent(QMouseEvent *);

		//移动鼠标调用这个事件函数
		void mouseMoveEvent(QMouseEvent *);

		//绘制函数，只能在这里绘制，不能在mouseMoveEvent中绘制
		//这里重新绘制整个窗口会把当前内容冲掉
		void paintEvent( QPaintEvent * /*e*/ );
	private:
		QPoint startP;
		QPoint endP;

};
#endif
