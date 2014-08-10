#include "myCallback.h"
#include <QFile>
#include <QString>
#include <QMouseEvent>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamAttributes>
#include <QtDebug>


MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
}
void MyCallback::mousePressEvent(QMouseEvent *e)
{
	clicked();
	e->ignore();
}
void MyCallback::clicked()
{
	QString fileName = "xmlSimple";
	QFile srcFile(fileName);

	if (!srcFile.open(QFile::ReadOnly | QFile::Text))
	{
		qDebug("Cann't open file!");
		return;
	}

	QXmlStreamReader reader(&srcFile);//这里实际也可以用字符串来初始化xml stream reader
	while (!reader.atEnd())
	{//是否读取到了文件的结尾
		qDebug()<<"read Next";
		reader.readNext();//读取下一个token,toker有许多类型例如开始标记，结束标记，注释等。
		if(reader.isStartElement())
		{//是否读取到了一个元素的开始标记例如,"<api>"
			qDebug()<<"reader.isStartElement:";
			QXmlStreamAttributes attr = reader.attributes();//返回元素开始的属性
			qDebug()<<reader.name().toString();//元素名，例如api,query等
			//qDebug()<<attr;
			if(attr.hasAttribute("ns"))
			{//判断是否有属性ns
				qDebug()<<attr.value("ns").toString();//返回"ns"的值
			}
			qDebug()<<attr.value("title").toString();//如果有title属性，那么返回相应值否则空。
		}
		if(reader.isCharacters())
		{//读取的是否是一个元素开始和结束标记中的文本
			qDebug()<<"reader.isCharacters:";
			//qDebug()<<reader.name().toString();//元素名，例如api,query等,这里应该是空
			qDebug()<<reader.text().toString();//不在元素之内的任意字符串，例如hello,空白等
		}
		if(reader.isEndElement())
		{//是否读取到了元素的结束标记,例如"</api>"
			qDebug()<<"reader.isEndElement:";
			//qDebug()<<reader.text().toString();//null,在这里应该是空
			qDebug()<<reader.name().toString();//同对应的startElement的元素名
		}
	}
	srcFile.close();
}
