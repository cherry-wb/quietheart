#include "myCallback.h"

#include <QLineEdit>
#include <QtDebug>


MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	init();
	updateLayout();
}

void MyCallback::init()
{
	setFixedHeight(ELINE_FIXHEIGHT);
	setContentsMargins(10,10,10,10);

	searchLine = new QLineEdit(this);

	searchBtn = new EPushLabel("Search", this);
	searchBtn->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	searchBtn->setFrameShape(QFrame::StyledPanel);

	clearBtn = new EPushLabel("Clear", this);
	clearBtn->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	clearBtn->setFrameShape(QFrame::StyledPanel);

	connect(searchBtn, SIGNAL(pressSignal()), this, SLOT(clicked()));
	connect(clearBtn, SIGNAL(pressSignal()), this, SLOT(clicked()));
	//connect(clearBtn, SIGNAL(pressSignal()), searchLine, SLOT(clear()));
}

void MyCallback::updateLayout()
{
	searchLine->setGeometry(0,0,width()*2/3,height());
	searchBtn->setGeometry(width()*2/3, 0, width()*1/6,height());
	clearBtn->setGeometry(width()*5/6, 0, width()*1/6,height());
}
void MyCallback::clicked()
{
	EPushLabel *btn = qobject_cast<EPushLabel *>(sender());
	if(btn->text() == "Search")
	{
		qDebug()<<btn->text()<<" clicked";
		qDebug()<<"line edit text is:"<<searchLine->text();
	}
	else if(btn->text() == "Clear")
	{
		qDebug()<<btn->text()<<" clicked";
		searchLine->clear();
	}
	else
	{
		qDebug()<<btn->text()<<" clicked";
		qDebug()<<"unknown clicked!";
	}
}
