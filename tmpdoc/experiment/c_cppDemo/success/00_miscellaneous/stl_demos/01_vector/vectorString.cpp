/*程序功能：测试vector的功能。
 * 具体为：
 * 1）将多个字符串插入到vector中。
 * 2)获得vector大小。
 * 3）将vector中的字符串取出并打印出来。
 *  使用迭代器，以及不用迭代器的方法。
 * 4）清空vector列表。
 * 5) 取出string字符串中的c风格char*字符串。
 * */
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(int argc, char *argv[])
{
	string str[3] = {"good", "better", "best"};
	
	//建立string类型的vector
	vector<string> strings;

	//向vector结尾追加元素
	for(int i = 0; i < 3; ++i)
	{
		strings.push_back(str[i]);
	}

	//打印vector元素数目
	cout<<"vector element count is:"<<strings.size()<<endl;

	//获取元素并打印,最原始的方法
	for(int i = 0; i < strings.size(); ++i)
	{
		string tmp = strings[i];
		//打印string字符串
		cout<<"the "<<i+1<<"th element is:"<<tmp<<endl;
		//另一种方式：取出string元素中的char*字符串再打印。
		cout<<"I say again:the"<<i+1<<"th element is:"<<tmp.c_str()<<endl;
	}
	cout<<"geting by iterator:"<<endl;
	//利用迭代器获取元素并打印
	vector<string>::iterator it;
	for(it = strings.begin(); it != strings.end(); ++it)
	{
		string tmp = *it;
		cout<<"the element by iterator is:"<<tmp.c_str()<<endl;
	}
	
	//删除vector中所有元素
	strings.clear();
	//判断是否为空
	if(strings.empty())
	{
		cout<<"the strings is empty! so size is:"<<strings.size()<<endl;
	}

	return 0;
}

