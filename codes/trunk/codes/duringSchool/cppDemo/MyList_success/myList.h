#ifndef __myList_h__
#define __myList_h__
//#ifndef MYNODETYPE int
//#define MYNODETYPE int
//#endif
#include<iostream.h>
#include"myListNode.h"
class MyList
{
public:
	MyList();
	~MyList();
	void add(int& node);//把一个元素插入到表头
//	void removeLast();
	void removeFirst();
	int length;//链表长度
	MyListNode* first;//指向第一个元素的指针（节点类型应该改变）
//	MyListNode* last;//指向最后一个元素的指针
	//MYNODETYPE num;//节点类型可以改变
	//MYNODETYPE *next;
};
#endif