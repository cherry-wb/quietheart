/*程序功能：
 * 把拼音表文件的格式进行一下转换，
 * 同样首列拼音的行合并。
 * 文件：
 * nipponIn.txt:一行只有一个字和相应的统计信息的原始拼音表,也是输入文件。
 * nipponOut.txt:输出文件，还没有处理过格式的问题。
 * nipponResult1.txt:使用vi处理后的nipponOut.txt,但是没有按照统计信息对字进行排序。
 * 其他的都是临时文件。
 *
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
	fstream fIn("./nipponIn.txt");
	fstream fOut("./nipponOut.txt");
//	char first[100] = {'\0'};//一行的行首拼音

	string first;
	string tmpFirst;
	string line;
	fIn>>first;//读取文件中的一个字符
	int iLine = 1;
	while(!fIn.eof())
	{//如果文件没有结束，处理每一行
//		fIn>>first;
		fOut<<first;//向文件中写入一个字符串
		std::getline(fIn,line);//读取文件当前位置到当前行尾的内容（无endl）
		fOut<<line;//no endl?
		fIn>>tmpFirst;
		cout<<"tmpFirst is:"<<tmpFirst<<endl;//写入字符串和行结束符号构成一行
		while(tmpFirst == first)
		{
			cout<<"line:"<<++iLine<<endl;
			if(std::getline(fIn,line))
			{
				fOut<<line;
				fIn>>tmpFirst;
			}
			else
			{
				break;
			}
		}
		fOut<<endl;
		first = tmpFirst;
	}
	fIn.close();
	fOut.close();
	return 0;
}
