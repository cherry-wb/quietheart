/*程序功能：测试c++中的string功能
 * 输入string之后，再次输入，然后打印string看是否第一次被第二次覆盖了。
 * 测试结果：是。
 * */
#include <iostream>
#include <string>
using std::endl;
using std::cout;
using std::cin;
using std::string;
int main(int argc, char *argv[])
{
	string test;
	cout<<"input first:"<<endl;
	cin>>test;
	cout<<"first time for test:"<<test<<endl;
	cout<<"input second:"<<endl;
	cin>>test;
	cout<<"second time for test:"<<test<<endl;
	return 0;
}
