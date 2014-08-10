#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDate>
#include <QDateEdit>
#include "myCallback.h"
#include <iostream>
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	d = QDate::currentDate().day();
	m = QDate::currentDate().month();
	y = QDate::currentDate().year();
	//timeEdit是一个显示时间的可编辑框
	dateEdit = new QDateEdit;
	//设置初始时间为当前时间
	dateEdit->setDate(QDate::currentDate());
	//设置显示的格式
	dateEdit->setDisplayFormat("yyyy/MM/dd");
	//设置日期范围(指定年月日)
	//注意文档说最小的日期不能够小于100/01/01，默认为1752/9/14（没有实践）。
	//如果超过范围那么就会自动调到最小或者最大
	dateEdit->setDateRange(QDate(1000,01,01),QDate(5000,01,01));

	//点击按钮改变时间中的时／分／秒
	btnD = new QPushButton( "date++");
	QObject::connect(btnD, SIGNAL(clicked()), this, SLOT(callbackD()));
	btnM = new QPushButton( "month++");
	QObject::connect(btnM, SIGNAL(clicked()), this, SLOT(callbackM()));
	btnY = new QPushButton( "year++");//实际秒的字段没有显示出来
	QObject::connect(btnY, SIGNAL(clicked()), this, SLOT(callbackY()));

	//hlayout
	QHBoxLayout *hlayout = new QHBoxLayout;
	hlayout->addWidget(btnD);
	hlayout->addWidget(btnM);
	hlayout->addWidget(btnY);

	//这里点击设置按钮则关闭程序
	//QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()));
	//button.show();//显示按钮

	//vlayout
	QVBoxLayout *vlayout = new QVBoxLayout;
	vlayout->addWidget(dateEdit);
	vlayout->addLayout(hlayout);

	this->setLayout(vlayout);
}

void MyCallback::callbackD(void)
{
	using std::cout;
	using std::endl;
	//获得当前光标所在位置是在时间的哪个段位置
	if(dateEdit->currentSection() == QDateTimeEdit::DaySection)
	{
		cout<<"called callback!in date!"<<endl;
		//获得当前timeEdit的时间
		QDate d(dateEdit->date());

		//先获得时间的时／分／秒然后设置时加1
		this->d = d.day();
		m = d.month();
		y = d.year();
		//这个QDate::setDate已经规定必须在一个特殊的很早日期之前
		d.setDate(y,m,++(this->d));

		dateEdit->setDate(d);
	}
	else
	{
		cout<<"called callback!not in date!"<<endl;
	}
}
void MyCallback::callbackM(void)
{
	using std::cout;
	using std::endl;

	if(dateEdit->currentSection() == QDateTimeEdit::MonthSection)
	{
		cout<<"called callback!in month!"<<endl;

		QDate d(dateEdit->date());

		//先获得时间的时／分／秒然后设置时加1
		this->d = d.day();
		m = d.month();
		y = d.year();
		d.setDate(y,++m,this->d);

		dateEdit->setDate(d);
	}
	else
	{
		cout<<"called callback!not in month!"<<endl;
	}
}
void MyCallback::callbackY(void)
{
	using std::cout;
	using std::endl;

	if(dateEdit->currentSection() == QDateTimeEdit::YearSection)
	{
		cout<<"called callback!in year!"<<endl;

		QDate d(dateEdit->date());

		//先获得时间的时／分／秒然后设置时加1
		this->d = d.day();
		m = d.month();
		y = d.year();
		d.setDate(++y,m,this->d);

		dateEdit->setDate(d);
	}
	else
	{
		cout<<"called callback!not in year!"<<endl;
	}
}
