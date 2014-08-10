//最多的顶点数 51个，正式程序中使用 
//#define N 51
//本例子顶点数是4个 
#ifndef __myGraph_h__
#define __myGraph_h__
#define DEBUGMYGRAPH 1//定义本文件的开关调试
#define N 4
#include<iostream>
#include<fstream>
#include "myVertex.h"
#include "myEdge.h"
// No description
class MyGraph
{
	public:
		// class constructor
		MyGraph();
		// class destructor
		~MyGraph();
		//随机生成一个图
		void generateGraph();
		//如果存在当前图则生成一个表示当前图的文件否则输入图存到一个文件中
		void createGraphFile();
		//读取图文件的函数
		void readGraph();
		//点
		//正式程序中V *Vertex 
#if DEBUGMYGRAPH == 1
		MyVertex1 Vertex[N];
#else
		MyVertex1 *Vertex;
#endif
		//边 
		//正式程序中是一个二维的动态数组怎么做??
#if DEBUGMYGRAPH == 1
		MyEdge Edge[N][N];
#else
		MyEdge **Edge;
#endif
		int n;//表示图中的节点总数
};
#endif