//另附测试自己程序运行时间的代码
//???不行？
#include<ctime>
#include<iostream>
using std::cout;
using std::endl;
int main()
{
	time_t start,finish;
	//time_t start=clock();
	start=clock();
	//cout<<start<<endl;
	for(int i = 0; i < 500000000; ++i)
	{
		//cout<<i<<endl;
		int tmp = i * 3;
	}
	
	//time_t finish=clock();
	finish=clock();
	//cout<<finish<<endl;
	//double e = static_cast<double>(finish - start) / CLOCKS_PER_SEC;
	cout<<double(finish - start) / CLOCKS_PER_SEC<<endl;
	return 0;
}























