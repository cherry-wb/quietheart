#include <QList>
#include <QPoint>
#include "myCallback.h"
#include <iostream>
MyCallback::MyCallback(QObject *parent):QObject(parent)
{
	;
}

void MyCallback::callback(void)
{
	using std::cout;
	using std::endl;
	static int count = 0;
	QPoint p1;
	p1.setX(1);
	QPoint p2;
	p2.setX(2);
	QPoint p3;
	p3.setX(3);
	QPoint p4;
	p4.setX(4);
	QPoint p5;
	p5.setX(5);

	switch(count)
	{
		case 0:
			cout<<"insert p1"<<endl;
			listPoints<<p1;
			++count;
			break;
		case 1:
			cout<<"insert p2"<<endl;
			listPoints<<p2;
			++count;
			break;
		case 2:
			cout<<"insert p3"<<endl;
			listPoints<<p3;
			++count;
			break;
		case 3:
			cout<<"insert p4"<<endl;
			listPoints<<p4;
			++count;
			break;
		case 4:
			cout<<"insert p5"<<endl;
			listPoints<<p5;
			++count;
			break;
		default:
			cout<<"clear!"<<endl;
			listPoints.clear();
			count = 0;
	}
	//返回列表元素数目,两种方法
	cout<<"the number of the list is:"<<listPoints.count()<<endl;
	//cout<<"the number of the list is:"<<listPoints.size()<<endl;
	
	//获取并打印所有元素,两种方法
	for(int i = 0; i < listPoints.size(); ++i)
	{
		//cout<<"the "<<i<<"th of point member, x is:"<<listPoints.at(i).x()<<endl;
		cout<<"the "<<i<<"th of point member, x is:"<<listPoints[i].x()<<endl;
	}
	cout<<"called callback!"<<endl;
}
