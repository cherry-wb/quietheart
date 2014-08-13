/*程序功能：测试数组的初始化值
 * 测试结果：
 * a,b的第一个元素是10,其他元素是0。
 * c的元素值都是随机的。
 * */
#include <iostream>
using std::cout;
using std::endl;
int main(int argc, char *argv[])
{
	int a[10] = {10};
	int b[10] = {10,9,};
	int c[10];

	cout<<"int a[10]={10};"<<endl;
	cout<<"int b[10]={10,9,};"<<endl;
	cout<<"int c[10];"<<endl;
	cout<<"the initialize value of a,b,c is:"<<endl;
	for(int i = 0; i < 10; ++i)
	{
		cout<<"a["<<i<<"]="<<a[i]<<endl;
		cout<<"b["<<i<<"]="<<b[i]<<endl;
		cout<<"c["<<i<<"]="<<c[i]<<endl;
	}
	//c = {1,2,};//这样的赋值是错误的，只能初始化的时候才能这样赋值
	//c = a;//这样的赋值是错误的
	//int d[10] = b;//这样的初始化也是错误的
	return 0;
}
