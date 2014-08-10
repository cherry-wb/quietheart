#include "mylist.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QSpacerItem>

MyList::MyList(QWidget *parent, Qt::WindowFlags f):QWidget(parent, f)
{
	itemCount = 0;
	setFixedSize(600,800);

	QLabel *title = new QLabel("MyTitle", this);
	title->setStyleSheet("background-color:#000000;color:#FFFFFF");
	title->setGeometry(0,0,width(), MY_TITLEHEIGHT);

	MyListItem *item1 = new MyListItem("filename", "text1",
					 "count", this);
	connect(item1, SIGNAL(clicked(MyListItem *)), 
		this, SLOT(clickResponse(MyListItem *)));
	appentItem(item1);

	MyListItem *item2 = new MyListItem("filename", "text2", 
					"count1", this);
	connect(item2, SIGNAL(clicked(MyListItem *)), 
		this, SLOT(clickResponse(MyListItem *)));
	appentItem(item2);

	MyListItem *item3 = new MyListItem("filename", "text3", 
					"count3", this);
	connect(item3, SIGNAL(clicked(MyListItem *)), 
		this, SLOT(clickResponse(MyListItem *)));

	appentItem(item3);
}
int MyList::iCount()const
{
	return itemCount;
}
void MyList::appentItem(MyListItem *item)
{
	if(iCount() < 8 && item != 0)
	{
		int itemHeight = (height() - MY_TITLEHEIGHT) >> 3;
		item->setParent(this);
		item->setGeometry(0, MY_TITLEHEIGHT + iCount()*itemHeight, 
				width(), itemHeight);
		++itemCount;
	}
}
void MyList::clickResponse(MyListItem *item)
{
	qDebug()<<"click item text is:"<<item->text();
}
