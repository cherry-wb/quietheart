#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <iostream>
#include "myCallback.h"
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	QSignalMapper *mapper = new QSignalMapper(this);
	QObject::connect(mapper, SIGNAL(mapped(const QString&)), this, SLOT(selBtn(const QString&)));

	hbox = new QHBoxLayout;
	setLayout(hbox);

	lbtn = new QPushButton("left");
	mapper->setMapping(lbtn, QString("left"));
	QObject::connect(lbtn, SIGNAL(clicked()), mapper, SLOT(map()));
	hbox->addWidget(lbtn);

	btn1 = new QPushButton("1");
	mapper->setMapping(btn1, QString("1st"));
	QObject::connect(btn1, SIGNAL(clicked()), mapper, SLOT(map()));
	hbox->addWidget(btn1);

	btn2 = new QPushButton("2");
	mapper->setMapping(btn2, QString("2nd"));
	QObject::connect(btn2, SIGNAL(clicked()), mapper, SLOT(map()));
	hbox->addWidget(btn2);

	btn3 = new QPushButton("3");
	mapper->setMapping(btn3, QString("3th"));
	QObject::connect(btn3, SIGNAL(clicked()), mapper, SLOT(map()));
	hbox->addWidget(btn3);

	rbtn = new QPushButton("right");
	mapper->setMapping(rbtn, QString("right"));
	QObject::connect(rbtn, SIGNAL(clicked()), mapper, SLOT(map()));
	hbox->addWidget(rbtn);

}

void MyCallback::selBtn(const QString &str)
{
	using std::cout;
	using std::endl;
	if(str == QString("left"))
	{
		QString tmpStr = lbtn->text();
		cout<<"button text is:"<<tmpStr.toLocal8Bit().data()<<endl;
		btn1->setText("1");
		btn2->setText("2");
		btn3->setText("3");
	}
	else if(str == QString("1st"))
	{
		QString tmpStr = btn1->text();
		cout<<"button text is:"<<tmpStr.toLocal8Bit().data()<<endl;
	}
	else if(str == QString("2nd"))
	{
		QString tmpStr = btn2->text();
		cout<<"button text is:"<<tmpStr.toLocal8Bit().data()<<endl;
	}
	else if(str == QString("3th"))
	{
		QString tmpStr = btn3->text();
		cout<<"button text is:"<<tmpStr.toLocal8Bit().data()<<endl;
	}
	else if(str == QString("right"))
	{
		QString tmpStr = rbtn->text();
		cout<<"button text is:"<<tmpStr.toLocal8Bit().data()<<endl;
		btn1->setText("4");
		btn2->setText("5");
		btn3->setText("6");
	}
}
