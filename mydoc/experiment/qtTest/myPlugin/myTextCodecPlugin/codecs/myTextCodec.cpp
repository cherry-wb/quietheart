#include "myTextCodec.h"
#include <QtDebug>
MyCodecPlugin::MyCodecPlugin(QTextCodecPlugin *parent):QTextCodecPlugin(parent)
{
	qDebug()<<"@@@@@@"<<__PRETTY_FUNCTION__;
}

QList<QByteArray> MyCodecPlugin::names() const
{
	return QList<QByteArray>() << "MyCode1" << "MyCode2";
}

QTextCodec *MyCodecPlugin::createForName(const QByteArray &name)
{
	qDebug()<<"@@@@@@"<<__PRETTY_FUNCTION__<<",the code text is:";
	if (name == "MyCode1")
	{
		qDebug()<<"MyCode1";
	}
	else if (name == "MyCode2")
	{
		qDebug()<<"MyCode2";
	}
	return 0;

}
QList<QByteArray> MyCodecPlugin::aliases () const
{
	return QList<QByteArray>() << "MyCode1" << "MyCode2";
}
QList<int> MyCodecPlugin::mibEnums () const
{
	return QList<int>() <<1<<2;
}
virtual QTextCodec *MyCodecPlugin::createForMib ( int mib )
{
	return new QTextCodec();
}
Q_EXPORT_PLUGIN2(mycodecplugin, MyCodecPlugin)
