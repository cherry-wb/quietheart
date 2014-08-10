#include<iostream>
using namespace std;
int main()
{
	//定义指针
	int** p1 = NULL;
	//int p1[][5];
	int** p2 = NULL;
	//int p2[][5];
	int n = 5;
	//分配空间
	p1 = new int*[n];
	int i = 0;
	for(i = 0; i < n; i++)
	{
		p1[i] = new int[n];//此处必须是方括号否则越界
	}
	for(i = 0; i < n; i++)
	{
		register int j = 0;
		for(j = 0; j < n; j++)
		{
			p1[i][j] = i*n + j;
			cout<<p1[i][j]<<',';
		}
	}
	//指针赋值
	p2 = p1;
	/*for(i = 0; i < n; i++)
	{
		p2[i] = p1[i];
	}
	for(i = 0; i < n; i++)
	{
		cout<<p1[i]<<':';
		cout<<p2[i]<<',';
	}*/
	//cout<<**p2;
	//访问指针
	for(i = 0; i < n; i++)
	{
		register int j = 0;
		for(j = 0; j < n; j++)
		{
			//p2[i][j] = i*n + j;
			cout<<p2[i][j]<<',';
			p2[i][j] = 1;
		}
	}/**/
	for(i = 0; i < n; i++)
	{
		register int j = 0;
		for(j = 0; j < n; j++)
		{
			//p2[i][j] = i*n + j;
			cout<<p1[i][j]<<',';
		}
	}
	//结果失败,二级动态指针之间不能直接赋值
	return 0;
}
