#include<iostream>
using std::cout;
using std::endl;
typedef int A[6];//技巧int A[6]是个变量，加上typedef相当于变量成了类型
int main()
{
	cout<<"start"<<endl;
	//A b;//相当于int b[6]了
	A b[5];	//由于typedef相当于int b[5][6]了
	int i = 0;
	int j = 0;
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 6; j++)
		b[i][j] = i*6 + j;
	}
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 6; j++)
		{
			cout<<b[i][j]<<',';
		}
		cout<<endl;
	}

	return 0;
}