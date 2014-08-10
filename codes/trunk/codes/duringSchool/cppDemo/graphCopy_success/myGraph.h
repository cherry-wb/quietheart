//最多的顶点数 51个，正式程序中使用 
//#define N 51
//本例子顶点数是4个 
#ifndef __myGraph_h__
#define __myGraph_h__
#define DEBUGMYGRAPH 1//定义本文件的开关调试
#define MAX 10000000
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
		//拷贝构造函数
		MyGraph(MyGraph& g);
		// class destructor
		~MyGraph();

		//随机生成一个图
		void generateGraph();
		//如果存在当前图则生成一个表示当前图的文件否则输入图存到一个文件中
		void createGraphFile();
		//读取图文件的函数
		void readGraph();
		//把原图改成具有n个节点的图
		setGraph(int n);
		//赋值重载
		MyGraph& operator=(MyGraph& g);
		//点
		//正式程序中V *Vertex 
		MyVertex1 *Vertex;
		//边 
		//正式程序中是一个二维的动态数组怎么做??
		MyEdge **Edge;
		int n;//表示图中的节点总数
};
#endif