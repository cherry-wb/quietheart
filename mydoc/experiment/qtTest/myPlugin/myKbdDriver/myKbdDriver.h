#ifndef __MYKBDDRIVER_H
#define __MYKBDDRIVER_H
class MyKbdDriver:public QKbdDriverPlugin
{
	public:
		MyKbdDriver::MyKbdDriver(QKbdDriverPlugin *parent = 0);
		QStringList keys() const;
		QWSKeyboardHandler *create(const QString &key, const QString &device);
};
#endif
