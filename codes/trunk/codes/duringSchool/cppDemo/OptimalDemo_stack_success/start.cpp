#include<iostream>
#include"myStack.h"
void main()
{
	//对堆栈的测试
	cout<<"start to test the stack:"<<endl;
	StackNode node[5];
	for(int i = 0;i < 5; i ++)
	{
		node[i].vertex.num = i;
	}
	for(int j = 0; j < 5; j++)
	{
		cout<<"第"<<j<<"个点:"<<node[j].vertex.num<<endl;
	}
	//node[3] = node[4];
	//cout<<node[3].vertex.num;
	//	node[3].vertex.num = 8;
	//	cout<<node[4].vertex.num;//没有java引用的问题
	
	
	cout<<"建立5个节点的堆栈stack1"<<endl;
	MyStack1 stack1(5);
	cout<<"stack1 top的初始值为："<<stack1.top<<endl;
	cout<<"压入节点号4"<<endl;
	stack1.push(node[4]);
	cout<<"top的值为："<<stack1.top<<endl;
	cout<<"压入节点号3"<<endl;
	stack1.push(node[3]);
	cout<<"top的值为："<<stack1.top<<endl;
	cout<<"获取栈顶元素："<<endl;
	StackNode tmpnode = stack1.getTop();
	cout<<tmpnode.vertex.num<<endl;
	cout<<"弹栈"<<endl;
	stack1.pop();
	cout<<"top的值为："<<stack1.top<<endl;
	cout<<"获取栈顶元素："<<endl;
	tmpnode = stack1.getTop();
	cout<<tmpnode.vertex.num<<endl;

	//[lkdebug
	cout<<stack1.top;
	//lkdebug]
	cout<<"建立4个节点的堆栈stack2"<<endl;
	MyStack1 stack2(4);
	cout<<"压入节点号1"<<endl;
	stack2.push(node[1]);
	cout<<"stack2 top的值为："<<stack2.top<<endl;
	cout<<"压入节点号2"<<endl;
	stack2.push(node[2]);
	cout<<"top的值为："<<stack2.top<<endl;
	cout<<"获取栈顶元素："<<endl;
	tmpnode = stack2.getTop();
	cout<<tmpnode.vertex.num<<endl;
	

	cout<<"把stack1复制到stack2中："<<endl;
	stack2 = stack1;
	cout<<"获取栈顶元素："<<endl;
	StackNode tmpnode2 = stack2.getTop();
	cout<<tmpnode2.vertex.num<<endl;


	cout<<"stack test over!success!!"<<endl;
	cout<<endl;
	
}