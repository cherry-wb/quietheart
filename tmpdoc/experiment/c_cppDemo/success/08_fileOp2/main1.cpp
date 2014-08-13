/*程序功能：
 *统计文件的行数
 * */
#include <iostream>
#include <string>
#include <fstream>
using std::cout;
using std::endl;
using std::string;
using std::fstream;
int main(int argc, char *argv[])
{
	fstream fIn("./nipponOut.txt");

	string first;//行首的罗马拼音
	string line;

	//调试用
	int lineNum = 0;//记录行数
	string test;

	while(!fIn.eof())
	{
		fIn>>first;//忽略第一个字符串（第一个字符串是罗马拼音）
		std::getline(fIn,line);//读取文件当前位置到当前行尾的内容（无endl）
		++lineNum;
	}
	cout<<"number of line is:"<<lineNum-1<<endl;
}
