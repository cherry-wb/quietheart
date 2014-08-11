#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QStringList>
#include <iostream>
#include "mySelectList.h"
using std::cout;
using std::endl;
MySelectList::MySelectList(QWidget *parent):QWidget(parent)
{
	QSignalMapper *mapper = new QSignalMapper(this);
	QObject::connect(mapper, SIGNAL(mapped(const QString&)), this, SLOT(pageBtn(const QString&)));

	hbox = new QHBoxLayout;
	setLayout(hbox);

	btnPrev = new QPushButton("prev");
	mapper->setMapping(btnPrev, QString("prev"));
	QObject::connect(btnPrev, SIGNAL(clicked()), mapper, SLOT(map()));
	hbox->addWidget(btnPrev);

	//每页的数目
	pn = PAGECOUNT;
	//当前所在页
	pg = 0;
	for(int i = 0; i < pn; ++i)
	{
		btn[i] = new QPushButton;
		btn[i]->setText(QString().setNum(i) + ".");
		//mapper->setMapping(btn[i], QString().setNum(i));
		//QObject::connect(btn[i], SIGNAL(clicked()), mapper, SLOT(map()));
		hbox->addWidget(btn[i]);
	}

	btnNext = new QPushButton("next");
	mapper->setMapping(btnNext, QString("next"));
	QObject::connect(btnNext, SIGNAL(clicked()), mapper, SLOT(map()));
	hbox->addWidget(btnNext);
}

const QString MySelectList::pageBtn(const QString &str)
{
	if(str == QString("prev"))
	{//向前翻页
		if(pg > 0)
		{
			--pg;
			refresh();
		}
		return QString("prev");
	}
	else if(str == QString("next"))
	{//向后翻页
		if(resultList.size()/(pn+1) > (pg -1))
		{
			++pg;
			refresh();
		}
		return QString("next");
	}
	//返回选中按钮的标签
	/*
	for(int i = 0; i < pn; ++i)
	{
		if(str == QString().setNum(i))
		{
			int indexN = pg*pn;
			if(indexN + i  < resultList.size())
			{
			//cout<<"selected button is:"<<btn[i]->text().toLocal8Bit().data()<<endl;
			cout<<"selected button text is:"<<resultList[indexN+i].toLocal8Bit().data()<<endl;
			//return btn[i]->text();
			return resultList[indexN+i];
			}
			else
			{//此处的问题：
				cout<<"nothing!"<<endl;
				//return QString("nothing");
				return QString();
			}
		}
	}
	*/
	cout<<"never reach here!"<<endl;
	return QString("error");
}
void MySelectList::setList(const QStringList &resultList)
{
	this->resultList=resultList;
	pg = 0;
}
void MySelectList::refresh()
{
		int indexN = pg*pn;
		for(int i = 0; i < pn; ++i)
		{
			//显示第几个,循环显示或者直接显示汉字的位置。
			//QString  textNum = QString().setNum(i + indexN) + ".";
			QString  textNum = QString().setNum(i) + ".";
			if(i+indexN < resultList.size())
			{
				setText(i,textNum + resultList[i+indexN]);//给第i个按钮设置显示的文字
			}
			else
			{
				setText(i,textNum);//给第i个按钮设置显示的文字
			}
		}
}
void MySelectList::setText(int i,QString s)
{
	if(i < pn)
	{
		btn[i]->setText(s);
	}
}
int MySelectList::getPn()const
{
	return pn;
}
int MySelectList::getPg()const
{
	return pg;
}
QPushButton* MySelectList::getNextBtn()const
{
	return btnNext;
}
QPushButton* MySelectList::getPrevBtn()const
{
	return btnPrev;
}
QString MySelectList::getSelChar(int n)
{
	if(resultList.size())
	{
		int indexN = pg*pn;
		if(indexN + n  < resultList.size())
		{
			//cout<<"selected button is:"<<btn[i]->text().toLocal8Bit().data()<<endl;
			cout<<"selected button text is:"<<resultList[indexN+n].toLocal8Bit().data()<<endl;
			//return btn[i]->text();
			return resultList[indexN+n];
		}
	}
	return QString().setNum(n);
}
/*
QPushButton** MySelectList::getBtnList()
{
	return &btn[0];
}
*/
