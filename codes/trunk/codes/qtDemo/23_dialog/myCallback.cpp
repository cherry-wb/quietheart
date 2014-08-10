#include <QPushButton>
#include <QDialog>
#include <QHBoxLayout>
#include <iostream>
#include "myCallback.h"


//////////mydialog
MyDialog::MyDialog(QWidget *parent):QDialog(parent)
{
	//这里设置对话框的外观，否则为空白对话框
	acceptBtn = new QPushButton(this);
	rejectBtn = new QPushButton(this);
	acceptBtn->setText("Accepted");
	rejectBtn->setText("Rejected");
	QHBoxLayout *hlay = new QHBoxLayout(this);
	setLayout(hlay);
	hlay->addWidget(acceptBtn);
	hlay->addWidget(rejectBtn);
	QObject::connect(acceptBtn, SIGNAL(clicked()), this, SLOT(acceptCallBack()));
	QObject::connect(rejectBtn, SIGNAL(clicked()), this, SLOT(rejectCallBack()));
}

void MyDialog::acceptCallBack()
{
	//setResult(QDialog::Accepted);
	done(QDialog::Accepted);//关闭并且设置结果为接受,会发送accepted信号
}

void MyDialog::rejectCallBack()
{
	//setResult(QDialog::Rejected);
	done(QDialog::Rejected);//关闭并且设置结果为拒绝,会发送rejected信号
}


///////MyCallback
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	//只有一个按钮，点击按钮可以弹出对话框
	btn = new QPushButton(this);
	QObject::connect(btn, SIGNAL(clicked()), this, SLOT(callback()));
}

void MyCallback::callback(void)
{
	using std::cout;
	using std::endl;
	MyDialog dlg(this);
	//这样使用exec可以让对话框阻塞后面的运行。否则后面的语句会自动执行。
	dlg.exec();

	if(dlg.result() == QDialog::Accepted)
	{
		cout<<"accepted!"<<endl;
	}
	else if(dlg.result() == QDialog::Rejected)
	{
		cout<<"rejected!"<<endl;
	}
	else
	{
		cout<<"unknown!"<<endl;
	}
	cout<<"called callback!"<<endl;
}
