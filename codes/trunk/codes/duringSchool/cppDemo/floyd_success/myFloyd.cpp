//关键考虑记录任意两点之间的最短路径
//把floyd封装到一个类里面
#include"myFloyd.h"
MyFloyd::MyFloyd()
{
	n = 0;
	cost = NULL;
}
MyFloyd::~MyFloyd()
{
	int i = 0;
	if(cost != NULL)
	{//释放cost的堆空间	
		for(i = 0; i < n; i++)
		{
			delete[]cost[i];
		}
		delete cost;
		cost = NULL;
		n = 0;
	}
}
void MyFloyd::compute(const MyGraph &g)
{
	cout<<"开始用floyd方法计算..."<<endl;
	n = g.n;
	int i = 0;
	int j = 0;
	int k = 0;
	//为代价矩阵分配动态空间
	cost = new int*[n];
	for(i = 0; i < n;i ++)
	{
		cost[i] = new int[n];
	}

	//初始化代价矩阵
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			cost[i][j] = g.Edge[i][j].cost;
		}
	}
	for(k = 0; k < n; k++)
	{
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
			{
				if(cost[i][j] > cost[i][k] + cost[k][j])
				{
					cost[i][j] = cost[i][k] + cost[k][j];
				}
			}
		}
	}
	cout<<"计算完毕，下面请看图中任意两点间的最短距离:"<<endl;
	for(i = 0; i < n; i ++)
	{
		for(j = 0; j < n; j++)
		{
			cout<<cost[i][j]<<',';
		}
		cout<<endl;
	}
}