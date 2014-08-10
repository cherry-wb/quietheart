#include "myCallback.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	QVBoxLayout *vbox= new QVBoxLayout(this);
	setLayout(vbox);

	//QStackedLayout可以添加多个widget,一次显示一个widget
	sw = new QStackedWidget;
	vbox->addWidget(sw);

	//默认显示第一个
	//label1 = new QLabel("label1", sw);//这样不行，这样在第一第二页都有这个标签了
	label1 = new QLabel("label1");//这样不行，这样在第一第二页都有这个标签了
	sw->addWidget(label1);

	label2 = new QLabel("label2");
	sw->addWidget(label2);

	label3 = new QLabel("label3");
	sw->addWidget(label3);

	//点击按钮，切换下一个标签页
	button = new QPushButton( "Next");
	connect(button, SIGNAL(clicked()), this, SLOT(showNext()));
	vbox->addWidget(button);
}

void MyCallback::showNext(void)
{
	static int index = 1;
	if(index > 2)
	{
		index = 0;
	}
	
	//设置显示的标签,index从0起。
	sw->setCurrentIndex(index);
	++index;

	//其他操作QStackLayout的函数还有
	//int currentIndex () const
	//QWidget * currentWidget () const
	//int count () const
	//QWidget * widget ( int index ) const
	//等等......
}
