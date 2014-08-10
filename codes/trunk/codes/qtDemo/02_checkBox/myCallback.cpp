#include "myCallback.h"

#include <QCheckBox>
#include <QtDebug>


MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	check1 = new QCheckBox("F&irst", this);
	check2 = new QCheckBox("S&econd", this);
	check3 = new QCheckBox("T&hird", this);

	//set object name for sender();
	check1->setObjectName("MyCheck1");
	check2->setObjectName("MyCheck2");
	check3->setObjectName("MyCheck3");

	check1->setGeometry(0,0,width()*2/3, height()/4);
	check2->setGeometry(0,height()/4,width()*2/3, height()/4);
	check3->setGeometry(0,height()/4*2,width()*2/3, height()/4);

	//set the state of check box
	//Qt::Unchecked,Qt::PartiallyChecked,Qt::Checked
	check1->setCheckState (Qt::Checked);//Qt::Checked is 2

	if(check1->checkState() == Qt::Checked)
	{
		qDebug()<<"check box1 checked!";
	}

	//connect signal when state of check box changed
	connect(check1,SIGNAL(stateChanged(int)),this,SLOT(stateChanged(int)));
	connect(check2,SIGNAL(stateChanged(int)),this,SLOT(stateChanged(int)));
	connect(check3,SIGNAL(stateChanged(int)),this,SLOT(stateChanged(int)));
}
void MyCallback::stateChanged(int state)
{
	//get object who send signal
	QCheckBox *check = qobject_cast<QCheckBox *>(sender());
	qDebug()<<"the state of check box"<<check->objectName()<<"changed to"<<state;
	qDebug()<<"so it's current state is:"<<check->checkState();
	qDebug()<<"it's text is:"<<check->text();
}
