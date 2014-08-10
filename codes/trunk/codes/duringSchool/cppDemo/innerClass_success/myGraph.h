//myGraph.h
#ifndef __myGraph_h__
#define __myGraph_h__
#define DEBUGMYGRAPH 1//定义本文件的开关调试
#define MAX 10000000
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
// No description
class MyGraph
{
	public:
		// class constructor
		class MyVertex;
		class MyEdge;
		MyGraph();
		//拷贝构造函数
		MyGraph(MyGraph& g);
		void print();
		// class destructor
		~MyGraph();

		//随机生成一个图
		void generateGraph(int n);
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
		MyVertex *Vertex;
		//边 
		//正式程序中是一个二维的动态数组怎么做??
		MyEdge **Edge;//(邻接矩阵)
		int n;//表示图中的节点总数
};
//图节点结构
class MyGraph::MyVertex
{
public:
	// class constructor
	MyVertex();
	// class destructor
	~MyVertex();
	// 点的度数
	int k;
	// 点号
	int num;
	
};

//图边的结构
class MyGraph::MyEdge
{
public:
	// class constructor
	MyEdge();
	// class destructor
	~MyEdge();
	// 判断是否是图中的一条边
	int isE;
	//记录该边被访问的次数
	int isVisited;
	//边的权值
	int cost;
};
#endif