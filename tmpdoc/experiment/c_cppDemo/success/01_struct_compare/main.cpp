/*程序功能：
 * 测试结构变量的比较
 *从这里我们可以看出，结构变量之间的比较，不能直接比较，虽然赋值可以直接。
 *比较两个结构体，可以使用string.h中的memcmp(const void*, const void*, size_t);
 *有一个疑问就是，由于不同的机器会对结构体进行填充，而填充的地方又可能包含垃圾信息，所以严格对结构的每个字节比较还是不妥当的，最好自己写一个针对结构体比较的函数。
 * */
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

typedef struct
{
	int x;
	int y;
}Point;
int main(int argc, char *argv[])
{
	Point p1 = {10,10};
	Point p2 = p1;
	Point p3 = {8,8};

	if(0 == memcmp(&p1,&p2,sizeof(Point)))
	{
		cout<<"p1 equals to p2"<<endl;
	}
	else
	{
		cout<<"p1 not equals to p2"<<endl;
	}

	if(0 == memcmp(&p1,&p3,sizeof(Point)))
	{
		cout<<"p1 equals to p3"<<endl;
	}
	else
	{
		cout<<"p1 not equals to p3"<<endl;
	}

	p1 = p3;
	if(0 == memcmp(&p1,&p3,sizeof(Point)))
	{
		cout<<"p1 equals to p3"<<endl;
	}
	else
	{
		cout<<"p1 not equals to p3"<<endl;
	}
	
	/*
	if(p1 == p2)
	{
		cout<<"p1 equals to p2"<<endl;
	}
	else
	{
		cout<<"p1 not equals to p2"<<endl;
	}
	if(p1 == p3)
	{
		cout<<"p1 equals to p3"<<endl;
	}
	else
	{
		cout<<"p1 not equals to p3"<<endl;
	}
	*/

	return 0;
}
