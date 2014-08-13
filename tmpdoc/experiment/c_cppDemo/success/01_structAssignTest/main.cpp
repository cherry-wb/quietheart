/*程序功能：
 * 测试结构变量的赋值
 * 在vector的情况下结构变量的赋值
 * 通过将数组嵌入到结构中，结构之间的赋值，达到数组赋值的目的，这样避免了数组赋值循环。
 * */
#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;
using std::cerr;

typedef struct
{
	int x;
	int y;
}Point;

struct myArray
{
	int a[10];
};
int main(int argc, char *argv[])
{
	Point p1 = {10,10};
	Point p2 = p1;
	Point p3;
	Point p4;
	vector<Point> points;
	cout<<"p1.x = "<<p1.x<<",p1.y = "<<p1.y<<endl;
	cout<<"p2.x = "<<p2.x<<",p2.y = "<<p2.y<<endl;
	points.push_back(p1);
	p3=points[0];
	cout<<"p3.x = "<<p3.x<<",p3.y = "<<p3.y<<endl;
	
	//p4 = {1,1};//这样赋值是错误的，只有初始化才能这样格式
	p4.x = 1;
	p4.y = 1;
	cout<<"p4.x = "<<p4.x<<",p4.y = "<<p4.y<<endl;

	//虽然数组之间不能直接赋值，但是可以通过将数组嵌入到结构中的方式给数组赋值。就不用循环了。
	myArray a1 = {{1,2,}};
	myArray a2;
	a2 = a1;
	for(int i = 0; i < 10; ++i)
	{
		cout<<"a1:"<<a1.a[i]<<endl;
		cout<<"a2:"<<a2.a[i]<<endl;
	}
	

	return 0;
}
