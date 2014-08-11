/*程序功能：
 * 在程序运行的时候设置控件的风格
 * 这里给出了设置常见风格的例子，这里的内容会不断地更新
 * */
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>
#include "myCallback.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QWidget window;
	window.resize(200,100);
	QVBoxLayout *hl = new QVBoxLayout();
	window.setLayout(hl);
	MyCallback *test1 = new MyCallback(0);
	hl->addWidget(test1);


	//////已经实践的好用的代码片段
	//指明包含的指定类型(QPushButton)的子控件的的stylesheet
	//test1->setStyleSheet("QPushButton,QPushButton:hover,QPushButton:pressed { color: red;background-color:white }");//这样有时候不管用
	test1->setStyleSheet("* { color: blue;background-color:white}");//所有的子类型前背景
	test1->setStyleSheet("QPushButton,QPushButton:hover,QPushButton:pressed { color:#FFFF00;background-color:#00FF00}");//qpushbutton背景绿色，文字黄色,覆盖了前面的设置

	//设置QLabel的背景图片,背景颜色，文字颜色
	QLabel *test2 = new QLabel("");
	test2->setStyleSheet("* { background-image: url(./load.png);background-position: top left;background-origin: content;}");
	hl->addWidget(test2);


	//设置QLabel的背景颜色和文字颜色
	QLabel *test3 = new QLabel("test3");
	test3->setStyleSheet("* {color: #FFFFFF;background-color:#000000}");
	hl->addWidget(test3);

	//////其他杂乱未实践的或者不清楚的代码片段供参考
	//test.setStyleSheet(" QPushButton:flat {border: none;}");
	//test.setStyleSheet("QPushButton:pressed {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #dadbde, stop: 1 #f6f7fa);}");
	//test.setStyleSheet("QPushButton { background-color: red }");

	//透明窗口
	//m_searchLoading->setStyleSheet("background-color: QColor(100,100,100,255);");//ok

	//frame边框
	//QFrame *frame = new QFrame(0);
	//frame->setStyleSheet("*{border: 2px solid green;}");//设置边框
	window.show();
	return app.exec();
}
