//this program used for i/o test
#include<iostream>
#include<cstdio>
using std::cout;
using std::cin;
using std::endl;

int main(void)
{
	int m = 0;
	int n = 0;
	int sum = 0;
	int count = 0;
	cout<<"begin!"<<endl;
	//test by method1 wrong
	//	while(cin.get()!='\n')continue;
	cout<<"method1:"<<endl;
	while(getchar()!='\n')
	{
		if(scanf("%d%d",&m,&n)!=2)
		{
			break;
		}
		++count;
		sum = m + n;
		printf("the sum of current group is:%d\n",sum);
		while(getchar()!='\n')continue;
	}
	printf("the count of input groups is:%d\n",count);

	//eatline
	while(cin.get()!='\n')continue;
	//test by method2 right
	cout<<"method2:"<<endl;
	count = 0;
	char c = '0';
	while(cin>>m>>n)
	{
		++count;
		sum = m+n;
		cout<<"the sum of current group is:"<<sum<<endl;
		/*if(cin.get()=='\n')
		{
			cout<<"the charactor is endline"<<endl;
		}*/
		while(cin.get() != '\n')continue;
		if((c = cin.get())=='\n')
		{
			cout<<"end input by endline"<<endl;
			break;
		}
		else
		{
			cin.putback(c);//put the char c geted by cin.get() back to the next of cin			
		}
	}
	cout<<"the count of input groups is"<<count<<endl;

	while(cin.get()!='\n')continue;

	//test by method3 wrong!
	cout<<"method3:"<<endl;
	count = 0;
	while(cin>>m>>n)
	{
		while(cin.get() != '\n')continue;
		if(cin.peek() == '\n')
		{//see the next character
			break;
		}
		++count;
		sum = m+n;
		cout<<"the sum of current group is:"<<sum<<endl;
		/*if(cin.get()=='\n')
		{
			cout<<"the charactor is endline"<<endl;
		}*/
	}
	cout<<"the count of input groups is"<<count<<endl;
	
	cout<<"ok!end!"<<endl;
	return 0;
}
