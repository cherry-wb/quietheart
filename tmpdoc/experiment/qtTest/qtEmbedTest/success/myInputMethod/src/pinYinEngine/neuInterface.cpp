#include "PinyinEngine.h"
#include "neuInterface.h"
#include <QString>
#include <iostream>
using std::cout;
using std::endl;

NeuPinYin::NeuPinYin()
{
	matched = 0;
}

NeuPinYin::NeuPinYin(QString &input)
{
	this->input_pinyin = input;
	matched = 0;
}

void NeuPinYin::setInput(QString &input)
{
	output_list.clear();
	matched = 0;
	this->input_pinyin = input;
}
void NeuPinYin::processInput()
{
	if(input_pinyin.length() > 0)
	{
		output_list.clear();
		//char table_file[] = "./pinyin_table.txt";
		//const char index_file[]="murphytalk_phrase_idx.txt";
		char table_file[] = "./cfg/pinyin_table.txt";
		const char index_file[]="./cfg/murphytalk_phrase_idx.txt";
		PinyinEngine ime(table_file,index_file);

		//获得匹配的数目
		//matched = ime.search((const char*)"pi");
		const char* tmpChar = input_pinyin.toLatin1().data();
		//cout<<"to be processed:"<<tmpChar<<endl;
		matched = ime.search(tmpChar);
		//cout<<"mathed:"<<matched<<endl;

		//获得匹配的所有字符串
		QChar tmp;
		for(int i = 0; i < matched; ++i)
		{
			tmp = ime.get_char(i);
			output_list<<QString(tmp);
		}
	}
}
QStringList& NeuPinYin::getResultList()
{
	return output_list;
}
int NeuPinYin::getMatchCount()
{
	return matched;
}
