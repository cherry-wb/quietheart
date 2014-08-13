/*程序功能：测试c++中的string功能
 * 输入string之后，再次输入，然后打印string看是否第一次被第二次覆盖了。
 * 测试结果：是。
 * */
#include <iostream>
#include <string>
using std::endl;
using std::cout;
using std::string;
int main(int argc, char *argv[])
{
	string test1;
	string test2;
	test1 = "test1";
	test2 = "test2";

//output string
	cout<<"before process:"<<test1<<','<<test2<<endl;
	
//string cat
	cout<<"strcat \"test\" + test1 + test2:"<<"test"+test1+test2<<endl;//testtest1test2

	string testall = "00"
					+test1
					+"11"
					+test2;
	cout<<"testall:"<<testall<<endl;
	testall = "  "
					+test1
					+"  "
					+test2;
	cout<<"testall:"<<testall<<endl;
	if(test1 == test2)
	{
		cout<<"test1 == test2"<<endl;
	}
	else
	{
		cout<<"test1 != test2"<<endl;
	}
	if(test1 == "test1")
	{
		cout<<"teset1=test1"<<endl;
	}

	int loc = test1.find("est",0);
	if(loc != string::npos )
	{
		cout<<loc<<endl;//here!,1
	}
	else
	{
		cout<<"no!"<<string::npos<<endl;//not here!
	}

	loc = test1.find("ttt",0);
	if(loc != string::npos)
	{
		cout <<loc<<endl;//not here!
	}
	else
	{
		cout<<"no!"<<string::npos<<endl;//here!,a very large number.
	}
	return 0;
}
