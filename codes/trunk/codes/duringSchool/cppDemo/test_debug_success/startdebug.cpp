#include<iostream.h>
void main()
{
	cout<<"hello,debug"<<endl;
	int a[8];
	a[4] = 0;
	int i = 5;
	i = 0;
	int j = 0;
	for(i = 0; i < 8; i++)
	{
	__asm
	{
		int 3
	};
		a[i] = i;
	}
	for(j = 0; j < 8; j++)
	{
		cout<<a[j]<<',';
	}
	cout<<endl;
}