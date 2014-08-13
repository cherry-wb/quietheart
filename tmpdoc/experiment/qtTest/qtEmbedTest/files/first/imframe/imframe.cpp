/*
	Author: shiroki@www.cuteqt.com
	License: GPLv2
*/

#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "imframe.h"
#include "inputwidget.h"

IMFrame::IMFrame()
{
	inputwidget = new InputWidget(this);
	inputwidget->show();
}

IMFrame::~IMFrame()
{
}

void IMFrame::sendContent(const QString& newcontent)
{
	content += newcontent;
	sendPreeditString(content,0);
}

void IMFrame::confirmContent()
{
	sendCommitString(content);
	content.clear();
}

void IMFrame::updateHandler(int type)
{
	switch(type)
	{
	case QWSInputMethod::FocusOut:
		content.clear();
		break;
	default:
		break;
	}
}
