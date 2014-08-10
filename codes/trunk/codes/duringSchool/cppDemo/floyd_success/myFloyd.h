#ifndef __myFloyd_h__
#define __myFloyd_h__
#include<iostream>
#include"myGraph.h"
class MyFloyd
{
public:
	MyFloyd();
	~MyFloyd();
	void compute(const MyGraph &g);//计算过程,外部调用的接口	
	int **cost ;//cost矩阵
	int n;//记录图的节点数

};
#endif