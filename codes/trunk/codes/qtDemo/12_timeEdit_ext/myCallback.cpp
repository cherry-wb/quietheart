#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTime>
#include <QTimeEdit>
#include "myCallback.h"
#include <iostream>
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	h = 0;
	m = 0;
	s = 0;
	//timeEdit是一个显示时间的可编辑框
	timeEdit = new QTimeEdit;
	//设置初始时间为当前时间
	timeEdit->setTime(QTime::currentTime());

	//点击按钮改变时间中的时／分／秒
	btnH = new QPushButton( "hour++");
	QObject::connect(btnH, SIGNAL(clicked()), this, SLOT(callbackH()));
	btnM = new QPushButton( "min++");
	QObject::connect(btnM, SIGNAL(clicked()), this, SLOT(callbackM()));
	btnS = new QPushButton( "sec++");//实际秒的字段没有显示出来
	QObject::connect(btnS, SIGNAL(clicked()), this, SLOT(callbackS()));

	//hlayout
	QHBoxLayout *hlayout = new QHBoxLayout;
	hlayout->addWidget(btnH);
	hlayout->addWidget(btnM);
	hlayout->addWidget(btnS);

	//这里点击设置按钮则关闭程序
	//QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()));
	//button.show();//显示按钮

	//vlayout
	QVBoxLayout *vlayout = new QVBoxLayout;
	vlayout->addWidget(timeEdit);
	vlayout->addLayout(hlayout);

	this->setLayout(vlayout);
}

void MyCallback::callbackH(void)
{
	using std::cout;
	using std::endl;
	//获得当前光标所在位置是在时间的哪个段位置
	if(timeEdit->currentSection() == QDateTimeEdit::HourSection)
	{
		cout<<"called callback!in hour!"<<endl;
		//获得当前timeEdit的时间
		QTime t(timeEdit->time());

		//先获得时间的时／分／秒然后设置时加1
		h = t.hour();
		m = t.minute();
		s = t.second();
		++h;
		t.setHMS(h,m,s);

		timeEdit->setTime(t);
	}
	else
	{
		cout<<"called callback!not in hour!"<<endl;
	}
}
void MyCallback::callbackM(void)
{
	using std::cout;
	using std::endl;

	if(timeEdit->currentSection() == QDateTimeEdit::MinuteSection)
	{
		cout<<"called callback!in minute!"<<endl;

		QTime t(timeEdit->time());

		//先获得时间的时／分／秒然后设置时加1
		h = t.hour();
		m = t.minute();
		s = t.second();
		++m;
		t.setHMS(h,m,s);

		timeEdit->setTime(t);
	}
	else
	{
		cout<<"called callback!not in minute!"<<endl;
	}
}
void MyCallback::callbackS(void)
{
	using std::cout;
	using std::endl;

	if(timeEdit->currentSection() == QDateTimeEdit::SecondSection)
	{
		cout<<"called callback!in second!"<<endl;

		QTime t(timeEdit->time());

		//先获得时间的时／分／秒然后设置时加1
		h = t.hour();
		m = t.minute();
		s = t.second();
		++s;
		t.setHMS(h,m,s);

		timeEdit->setTime(t);
	}
	else
	{
		cout<<"called callback!not in second!"<<endl;
	}
}
