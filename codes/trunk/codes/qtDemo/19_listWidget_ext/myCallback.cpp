#include "myCallback.h"
#include <QString>
#include <QListWidgetItem>
#include <QListWidget>

//#include <QAbstractItemView>
#include <iostream>
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	listWidget = new QListWidget(this);
	//指定方向是从左到右，默认是QListView::TopToBottom,超过边界了可以试试setWrapping
	listWidget->setFlow(QListView::LeftToRight);
	
	//item一般用来在list中显示文字和图标
	//添加item方法1
	//建立item时直接指定item父窗口为存在的listWidget就可以添加
	item1 = new QListWidgetItem(QObject::tr("item1"), listWidget);

	//添加item方法2
	//先建立item，再用listWidget主动添加（可以插入）
	item2 = new QListWidgetItem;
	item2->setText(QString("item2"));
	listWidget->addItem(item2);

	//添加item方法3
	//不用建立item，直接用listWidget指定添加的标签就可以建立并插入item
	listWidget->addItem(QString("item"));

	//给定位置获得item,位置从0开始
	//可以给定一个QPoint返回一个item，没有实践过
	item3 = listWidget->item(2);
	item3->setText(QString("item3"));


	listWidget->addItem(QString("item"));
	listWidget->addItem(QString("item"));
	listWidget->addItem(QString("item"));
	listWidget->addItem(QString("item"));
	listWidget->addItem(QString("item"));
	listWidget->addItem(QString("item"));
	listWidget->addItem(QString("item"));
	listWidget->addItem(QString("item"));
	listWidget->addItem(QString("item"));
	listWidget->addItem(QString("item"));
	listWidget->addItem(QString("item"));
	listWidget->addItem(QString("item"));
	listWidget->addItem(QString("item"));
	listWidget->addItem(QString("item"));
	listWidget->addItem(QString("item"));
	listWidget->addItem(QString("item"));
	//设置item选择的模式为多选，其他的值如下：
	//QAbstractItemView::SingleSelection:单选
	//QAbstractItemView::ContiguousSelection:如果按shift则选择新旧item之间的
	//QAbstractItemView::MultiSelection：多选并且可以toggle
	//QAbstractItemView::NoSelection：不可选
	//QAbstractItemView::ExtendedSelection:高级选择添加ctrl,shift,拖拽和toggle等
	listWidget->setSelectionMode(QAbstractItemView::MultiSelection);

	//设置单击item的响应
	QObject::connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)),
			this, SLOT(clickedItem(QListWidgetItem*)));
}

void MyCallback::clickedItem(QListWidgetItem *item)
{
	using std::cout;
	using std::endl;
	//获得item上面的字
	QString text(item->text());

	cout<<"clicked at:"<<text.toLocal8Bit().data()<<endl;
	if(item->isSelected())
	{
		cout<<"the item is selected"<<endl;
	}
}
