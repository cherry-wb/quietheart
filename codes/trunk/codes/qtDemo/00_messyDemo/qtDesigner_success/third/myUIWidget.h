#ifndef __MYUIWIDGET_H
#define __MYUIWIDGET_H
#include "ui_untitled.h"
class MyWidget:public QMainWindow, private Ui::MainWindow
{//这里继承顺序不能变化！
	Q_OBJECT
	public:
		MyWidget(QMainWindow *parent = 0);
	private slots:
		//这里可以定义自己的槽
};
#endif
