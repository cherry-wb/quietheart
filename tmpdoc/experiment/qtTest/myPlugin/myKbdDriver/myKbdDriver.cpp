#include "myDbdDriver.h"
#include <QtDebug>
MyKbdDriver::MyKbdDriver(QKbdDriverPlugin *parent)QKbdDriverPlugin(parent)
{
	qDebug()<<"hello"<<__PRETTY_FUNCTION__;
}
QStringList MyKbdDriver::keys()const
{
	return QStringList() << "MyKbd";
}
QWSKeyboardHandler *MyKbdDriver::create(const QString &key,const Qstring &device)
{
	if (key.toLower() == "mykbd")
		return new MyKbdDriver;
	return 0;
}
