#include<iostream>
//包含头文件
#include"myGraph.h"
using namespace std;
int main()
{
	cout<<"begin test myGraph:"<<endl;
	MyGraph g;//建立图对象
	g.readGraph();//读取文件生成相应的图
	g.print();//打印图的信息.
	g.createGraphFile();//输出图到一个output.txt文件中
	MyGraph g1(g);//用拷贝构造函数初始化图
	g1.print();
	MyGraph g2;
	g2 = g1;//复制
	g2.print();
	g2.setGraph(6);//给g2重新置为6个节点
	cout<<"重置后:"<<endl;
	g2.print();

	return 0;
}