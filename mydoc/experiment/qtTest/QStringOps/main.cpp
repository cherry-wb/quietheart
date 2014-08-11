/*程序功能：测试QString的一些常用操作功能，不断更新。
 * */
#include <QString>
#include<QDebug>
#include <QApplication>
#include <QStringList>
#include <iostream>
using std::cout;
using std::endl;
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	//////insert(ok)
	QString s("test"); s.insert(2,QString("%"));//
	qDebug()<<s;//"te%st"

	//////用c的标准方式输出ok
	char *a = s.toLocal8Bit().data();
	cout<<a<<endl;//"te%st"

	//////参数转换ok
	int i = 3;
	//注意这里是数字%1,不是字母%l
	QString s1 = QString("button%1").arg(i);//button3
	QString s2(QString("%1").arg(i,2,10,QChar('0')));//button03,arg参数分别是：整数，宽度，基数，填充字符。
	qDebug()<<s1;

	//////字符串转换成字符串列表ok
	//QString lenStr = "1234567890";
	//QStringList toShort = lenStr.toStringList();
	//qDebug()<<toShort;

	QString args = "first second third";
	QStringList argList = args.split(" ");
	qDebug()<<argList;//("first","second","third")

	//////判断字符串是否以某个子串结尾ok
	QString file = "test.cpp";
	if(file.endsWith(".cpp"))
	{
		qDebug()<<"ends with .cpp";
	}
	//mid

	//////大小写转换ok
	QString testLower = "Test";
	qDebug()<<testLower.toLower();


	//////去掉子串,或者截取子字符串ok
	QString fileExt = "test.txt";
	fileExt.chop(3);//去掉后三个字符,"test."
	qDebug()<<fileExt;

	QString fileExt2 = "tttttest.jpeg";
	QString fileExt3 = fileExt2;

	//获取从右向左遇到的第一个'.'的位置（位置当然是从左面算的）
	int index = fileExt2.lastIndexOf('.');//8
	qDebug()<<"last index of text.jpeg, the . is at:"<<index;

	fileExt2.chop(fileExt2.length()-index);//去掉指定位置(包括该位置)之后的内容,结果"tttttest"
	qDebug()<<fileExt2;

	//截取子串如下
	//QString::mid ( int position, int n = -1 ) const:这个函数返回从position开始，n长度的子串
	//n=-1是默认，表示一直到结尾
	qDebug()<<fileExt3.mid(index+1);//"jpeg"

	//空字符串
	QString pos=NULL;
	qDebug()<<"pos.isEmpty:"<<pos.isEmpty();

	//格式化地存储字符串
	QString strfmt;
	strfmt.sprintf("%ld.%06ld", 10, 20);
	qDebug()<<strfmt;//"10.000020"


	return 0;
}
