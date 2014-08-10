#include<iostream>
#include"myGraph.h"
void copyToG(MyGraph& g1)
{
	MyGraph g;
	g.readGraph();
	cout<<"print g:"<<endl;
	int i = 0;
	int j = 0;
	cout<<g.n<<endl;
	for(i = 0; i < g.n; i++)
	{
		cout<<g.Vertex[i].num<<',';
		cout<<g.Vertex[i].k<<';';
	}
	cout<<endl;
	for(i = 0; i < g.n; i++)
	{
		for(j = 0; j < g.n; j++)
		{
			cout<<i<<','<<j<<','<<g.Edge[i][j].cost<<endl;
		}
	}
	g1 = g;
	cout<<"¿½±´½áÊø!"<<endl;
}
void main()
{
	cout<<"hello,begin test!"<<endl;
	MyGraph g1;
	copyToG(g1);
	int i = 0;
	int j = 0;
	cout<<"print g1:"<<endl;
	cout<<g1.n<<endl;
	for(i = 0; i < g1.n; i++)
	{
		cout<<g1.Vertex[i].num<<',';
		cout<<g1.Vertex[i].k<<';';
	}
	cout<<endl;
	for(i = 0; i < g1.n; i++)
	{
		for(j = 0; j < g1.n; j++)
		{
			cout<<i<<','<<j<<','<<g1.Edge[i][j].cost<<endl;
		}
	}
}