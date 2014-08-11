/*程序功能：
 * 测试拼音输入法的引擎，输入一个拼音同时输出相应中文字列表
 * 例如：$./test pin
 * 将输出所有拼音为"pin"的汉子列表.
 * */
#include <QString>
#include <QStringList>
#include <iostream>
#include "./pinYinEngine/neuInterface.h"
using std::cout;
using std::endl;
int main(int argc, char *argv[])
{
	cout<<argc<<endl;
	if(argc != 2)
	{
		cout<<"Usage:"<<argv[0]<<" input(pinyin)"<<endl;
		return 1;
	}

	NeuPinYin test;
	QStringList matchList;
	int matchCount = 0;

	//cout<<argv[1]<<":"<<endl;;
	QString tmp(argv[1]);
	test.setInput(tmp);
	test.processInput();

	matchList = test.getResultList();
	matchCount = test.getMatchCount();

	cout<<"the count of match is:"<<matchCount<<endl;
	cout<<"the count of match is:"<<matchList.size()<<endl;

	//打印所有匹配的转换后的字符
	for(int i = 0; i < matchList.size(); ++i)
	{
		cout<<i<<","<<matchList[i].toUtf8().data();
	}
	cout<<endl;

	return 0;
}
