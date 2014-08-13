/*程序功能：分割字符串
 * 首先读取文件nipponOut.txt中的某一行，
 * 然后统计这一行中除了第一个字符串之外还有多少个字符串
 * */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::fstream;

vector<string> split(const std::string &s);
int main(int argc, char *argv[])
{
	fstream fIn("./nipponOut.txt");

	string first;//行首的罗马拼音
	string line;

	vector<string> stringList;//存放一行中的每一个子字符串

	//调试用
	string test;

	int lineNum = 0;//记录行数
	int n = 16;
	
	//统计第n行文字的个数
	fIn>>first;//忽略第一个字符串（第一个字符串是罗马拼音）
	while(!fIn.eof() && lineNum < n)
	{
		std::getline(fIn,line);//读取文件当前位置到当前行尾的内容（无endl）
		++lineNum;
		fIn>>first;//忽略下一行第一个字符串（第一个字符串是罗马拼音）
	}
	stringList = split(line);
	cout<<"number in line is:"<<stringList.size()<<endl;
}

//分割字符串
vector<string> split(const std::string &s)  
{  
	vector<string> vec_ret;  
	typedef string::size_type string_size;  
	string_size i = 0;  
	while (i != s.size()){  
		while (i != s.size() && isspace(s[i]))  
			++i;  
		string_size j = i;  
		while (j != s.size() && !isspace(s[j]))  
			++j;  
		if (i != j){  
			vec_ret.push_back(s.substr(i, j-i));  
			i = j;  
		}  
	} 
	return vec_ret;  
}
