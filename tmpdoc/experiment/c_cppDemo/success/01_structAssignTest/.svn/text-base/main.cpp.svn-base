/*程序功能：
 * 测试结构变量的赋值
 * 在vector的情况下结构变量的赋值
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
	

	return 0;
}
