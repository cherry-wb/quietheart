/*
	Author: shiroki@www.cuteqt.com
	License: GPLv2
*/

#ifndef IMFRAME_H
#define IMFRAME_H

#include <QWSInputMethod>

class InputWidget;
class IMFrame:public QWSInputMethod
{
Q_OBJECT
public:
	IMFrame();
	~IMFrame();
	void setMicroFocus(int, int);
	void updateHandler(int);

private:
	InputWidget* inputwidget;
	QString content;

private slots:
	void sendContent(const QString&);
	void confirmContent();
};

#endif
