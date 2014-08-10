#include "myCallback.h"

#include <QMenu>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QtDebug>

////////主类
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	m_menu = new QMenu();

	//////方法1，使用QWidgetAction和自定义的一个widget来实现自定义的Action.
	MyCustomWidget *my = new MyCustomWidget(this);
	QWidgetAction *myaction1 = new QWidgetAction(m_menu);
	//设置action相应的自定义widget"容器"
	//这样，就可以把自定义的widget "看做" action了，定制自己想要的"action".
	//有时候这需要那个widget容器来调用QAction的triggered().这里如果点标签就不用。
	//点击按钮就得发送一个triggered给action.
	myaction1->setDefaultWidget(my);
	//myaction1->setText("myaction1");//看不到效果
	m_menu->addAction(myaction1);
	//通过这个发起action的triggle信号，否则点击按钮的时候就无法捕获action的trigger信号了
	connect(my,SIGNAL(triggleAction()), myaction1, SIGNAL(triggered()));
	connect(myaction1, SIGNAL(triggered()),this,SLOT(do1()));

	//////方法2，继承QWidgetAction来实现一个自定义的Action
	MyWidgetAction *myaction2 = new MyWidgetAction(this);
	m_menu->addAction(myaction2);
	connect(myaction2, SIGNAL(triggered()), this, SLOT(do2()));
}

void MyCallback::mousePressEvent(QMouseEvent *event)
{
	m_menu->move(event->globalX(),event->globalY());
	m_menu->exec();
}

void MyCallback::do1()
{
	qDebug()<<"myaction1 clicked!";
}

void MyCallback::do2()
{
	qDebug()<<"myaction2 clicked!";
}

////////"容纳"QAction的自定义Widget类，相当于我们看到的QAction"外观"
MyCustomWidget::MyCustomWidget(QWidget *parent):QWidget(parent)
{
	label = new QLabel("lbl:", this);
	btn = new QPushButton("btn", this);

	QHBoxLayout *hl = new QHBoxLayout(this);
	setLayout(hl);

	hl->addWidget(label);
	hl->addWidget(btn);

	connect(btn, SIGNAL(clicked()), SLOT(clicked()));
}

void MyCustomWidget::clicked()
{
	qDebug()<<"button clicked!";
	//需要借用这个来发送triggleAction信号给Action连接，否则点击按钮就不会发起action的信息了.
	emit triggleAction();
}

////////一个自定义的QWidgetAction
MyWidgetAction::MyWidgetAction(QObject*p):QWidgetAction(p)
{
	widget = new MyCustomWidget;

	//通过这个发起action的triggle信号，否则可能就无法捕获action的trigger信号了
	connect(widget,SIGNAL(triggleAction()), this, SIGNAL(triggered()));
	connect(this, SIGNAL(toggled(bool)), this, SLOT(changeCheckState(bool)));
	//setText("My text");
	//setIconText("My icon text");
	//setIcon(QIcon("./cuteqt.png"));
	setCheckable(true);
	setChecked(true);
}

//返回一个用来“表示”QAction的自定义的widget,一般其父窗口是Action将要添加的地方
QWidget* MyWidgetAction::createWidget(QWidget*p)
{
	if(p->inherits("QToolBar"))
	{//如果是想要添加到ToolBar上面，暂且不让这样做（返回空）
		qWarning() << "toolbar...";
		return 0;
	}   
	else if( p->inherits("QMenu"))
	{//如果添加到QMenu上面，就将自定义的widget返回
		qWarning() << "menu...";
		widget->setParent(p);
		return widget;
	}
	return 0;
}

void MyWidgetAction::changeCheckState(bool chk)
{
	qDebug()<<"check state:"<<chk;
}

