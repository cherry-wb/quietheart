#include<iostream.h>
#include"myList.h"
void main()
{
	cout<<"hello myList:"<<endl;
	MyList list;
	cout<<"定义一个链表对象。"<<endl;
	cout<<"删除链表首元素"<<endl;
	list.removeFirst();
	int a = 1;
	cout<<"加入元素1"<<endl;
	list.add(a);
	a = 2;
	cout<<"加入元素2"<<endl;
	list.add(a);
	a = 3;
	cout<<"加入元素3"<<endl;
	list.add(a);
	cout<<"长度："<<list.length<<endl;
	cout<<"用length从头察看链表元素结果如下:"<<endl;
	MyListNode* p = list.first;
	for(int i = 0; i < list.length; i ++)
	{
		cout<<p->element<<',';
		p = p->next;
	}
	cout<<endl;
	cout<<"用最后一个元素是否为空从头察看链表元素结果如下:"<<endl;
	for(p = list.first; p != NULL; p = p->next)
	{		
		cout<<p->element<<',';
	}
	cout<<endl;
	cout<<"开始去掉首元素"<<endl;
	list.removeFirst();
	cout<<"长度："<<list.length<<endl;
	cout<<"开始去掉所有元素"<<endl;
	//for(int j = 0; j < list.length; j ++)//注意length也是动态变化的
	while(list.length != 0)
	{
		list.removeFirst();
	}
	cout<<"长度："<<list.length<<endl;
	cout<<"再删除链表首元素"<<endl;
	list.removeFirst();
	cout<<"测试完毕!"<<endl;
}