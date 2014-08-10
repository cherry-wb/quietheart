#include "myEdge.h" // class's header file
#include <iostream>
using namespace std;
// class constructor
MyEdge::MyEdge()
{
	// insert your code here
	isE = 0; 
	isVisited = 0;
}

// class destructor
MyEdge::~MyEdge()
{
	// insert your code here
}

// 根据时间获取该边的代价的函数根据图的不同而不同在此是一个例子 
int MyEdge::getCost(int i,int j,int t)
{
	/* TODO (#1#): Implement E::getCost() */
	int time = t;
	//if(isE == 1)
	//{	
		if(time >= 0)
		{
			while(time > 15000)
			{
				time = time - 15000;
			}
			if(time < 5000)
			{
				return 100;
			}
			if(time < 10000)
			{
				return 200;
			}
			return 100;
		}
		else
		{
			int a = 1;
			cout<<"时间不能为负数"<<endl;
			return -1; 
		}
	//}
	//else
	//	cout<<"没有这条边!"<<endl;
}
int MyEdge::getCost2(int i,int j,int t)
{
	/* TODO (#1#): Implement E::getCost() */
	int time = t;
	//if(isE == 1)
	//{	
	if(time >= 0)
	{
		while(time > 15000)
		{
			time = time - 15000;
		}
		if(time < 5000)
		{
			return 2000;
		}
		if(time < 10000)
		{
			return 3000;
		}
		return 2000;
	}
	else
	{
		int a = 1;
		cout<<"时间不能为负数"<<endl;
		return -1; 
	}
	//}
	//else
	//	cout<<"没有这条边!"<<endl;
}