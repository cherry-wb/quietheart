#ifndef __NEUINTERFACE_H
#define __NEUINTERFACE_H

#include <QStringList>
class QString;

class NeuPinYin
{
	public:
	NeuPinYin();
	NeuPinYin(QString &input);

	//设置待处理的字符
	void setInput(QString &input);

	//处理待处理的字符
	void processInput();

	//获得处理后的结果
	QStringList &getResultList();

	//获得匹配的数目
	int getMatchCount();

	private:
	QString input_pinyin;
	QStringList output_list;
	int matched;

};
#endif
