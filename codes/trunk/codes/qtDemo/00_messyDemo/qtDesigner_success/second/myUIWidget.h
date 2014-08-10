#ifndef __MYUIWIDGET_H
#define __MYUIWIDGET_H
#include"ui_untitled.h"
class MyWidget:public QMainWindow
{
	Q_OBJECT
	public:
		MyWidget(QMainWindow *parent = 0);
	private slots:
		//在这里可以定义自己的槽
//		void on_inputSpinBox1_valueChanged(int value);
//		void on_inputSpinBox2_valueChanged(int value);

	private:
		Ui::MainWindow ui;

};
#endif
