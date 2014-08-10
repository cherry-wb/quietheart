#include "myCallback.h"

#include <QComboBox>
#include <QtDebug>


MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	comboBox= new QComboBox(this);

	//add a item to combo box
	comboBox->addItem(QString("first"));
	comboBox->addItem(QString("second"));
	comboBox->addItem(QString("third"));

	//get the total count of combo box
	qDebug()<<"the item count of the combo box is:"<<comboBox->count();

	//set the current actived item
	comboBox->setCurrentIndex(1);//the first is 0,which is default
	qDebug()<<"the current index is:"<<comboBox->currentIndex();

	//can edit
	comboBox->setEditable(true);//default is false

	//connect the signal
	connect(comboBox,SIGNAL(activated(int)),
		this,SLOT(actived(int)));
	connect(comboBox,SIGNAL(activated(const QString&)),
		this,SLOT(actived(const QString&)));
}

void MyCallback::actived(int index)
{
	qDebug()<<"The actived index is:"<<index;
	qDebug()<<"item text is:"<<comboBox->itemText(index);
}

void MyCallback::actived(const QString &text)
{
	qDebug()<<"The actived text is:"<<text;
}
