#include<iostream.h>
void test()
{
	cout<<"开始测试动态二维指针.."<<endl;
	int m;
	cout<<"请输入维数:"<<endl;
	cin>>m;
	cout<<"开始创建"<<m<<"维的动态数组"<<endl;
	//创建二维数组
	int **p;
	p = new int*[m];
	int i = 0;
	int j = 0;
	for(i = 0; i < m; i++)
	{
		p[i] = new int[m];
	}
	//测试创建的数组
	int count = 0;
	for(i = 0; i < m; i++)
	{
		for(int j = 0; j < m; j++)
		{
			p[i][j] = count ++;
			cout<<p[i][j];
		}
	}
	//释放动态二维数组
	for(i = 0; i < m; i++)
	{
		delete[]p[i];
		p[i] = NULL;
	}
	delete []p;
	p = NULL;
	//释放之后的测试
}
void main()
{
	test();
}
