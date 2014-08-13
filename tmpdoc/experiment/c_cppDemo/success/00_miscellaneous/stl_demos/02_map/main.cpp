/*程序功能：测试stl中map的映射。map不是hash的.
 * 如果想要更高的效率，可以用hash_map,用法是一样的，但是它还没有包含到标准库
 * 功能包括：
 * 建立一个映射表
 * 存储一个key,value对
 * 根据key取出value
 * key和value关系应该是一个key，一个value的？
 * */
#include <iostream>
#include <string>
#include <map>
using std::cout;
using std::endl;
using std::map;
using std::string;

int main(int argc, char *argv[])
{

	//建立一个映射表
	map<string,int> myMap;
	
	//添加映射
	myMap["first"] = 1;
	myMap["second"] = 2;
	myMap["third"] = 3;

	//根据键查找值
	if(myMap.find("second") != myMap.end())
	{
		int i = myMap["second"];
		cout<<"the map is:"<<i<<endl;
	}
	return 0;
}
