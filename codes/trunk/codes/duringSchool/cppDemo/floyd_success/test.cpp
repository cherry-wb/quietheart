#include<iostream>
#include"myGraph.h"
#include"myFloyd.h"
void main()
{
	cout<<"hello test floyd!"<<endl;
	MyGraph g;
	g.readGraph();
	MyFloyd floyd;
	floyd.compute(g);
}