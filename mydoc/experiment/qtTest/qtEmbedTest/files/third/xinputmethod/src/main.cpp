/**********************************************************************
** Copyright (C) 2009 InsideQt.com
**
** This file is part of the Input Method Programming Guideline,
** for Qt/Embedded 4.5.1 
** Official named as Qt 4.5.1 for Embedded Linux 
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 3 as published by the Free Software
** Foundation 
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** 
** Author:      Q-Kevin
** email:       qkevin@InsideQt.com
** Homepage:    http://www.InsideQt.com
** Create Date: May 11, 2009
** License:     GPL version 3 or later
** 
** Please visist http://www.InsideQt.com/bbs to get more details 
**********************************************************************/


#include <QApplication>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QTextCodec>
#include <QLabel>
#include <QString>
#include "xinputmethod.h"
#include "ximewindow.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    const QApplication::Type type = app.type();

    QMainWindow mw;
	
    if (QApplication::GuiServer == type)
    {
        XInputMethod::installInputMethod();
    }

    QPlainTextEdit pte(&mw);
    mw.setCentralWidget(&pte);

    mw.show();

    int nret = app.exec();

    if (QApplication::GuiServer == type)
        XInputMethod::releaseInputMethod();

    return nret;
}

