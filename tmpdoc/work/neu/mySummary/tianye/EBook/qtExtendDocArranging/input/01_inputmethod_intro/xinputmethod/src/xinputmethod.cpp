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


#include <QWSServer>
#include <QApplication>
#include <QTextCodec>
#include <QStringList>

#include "ximedata.h"
#include "ximewindow.h"
#include "xinputmethod.h"



struct XInputMethodPrivate
{
	static XInputMethod* pInputMethod;

	XWindow* pframe;

	XData imedata;

	XInputMethodPrivate(): pframe(NULL) {}
};


XInputMethod* XInputMethodPrivate::pInputMethod = NULL;

void XInputMethod::installInputMethod()
{
    XInputMethod* pim = instance();
   
    if (pim)
    {
        QWSServer::setCurrentInputMethod(pim);
    }
}

void XInputMethod::releaseInputMethod()
{
    if (XInputMethodPrivate::pInputMethod)
    {
        QWSServer::setCurrentInputMethod(NULL);
        delete XInputMethodPrivate::pInputMethod;
        XInputMethodPrivate::pInputMethod = NULL;
    }
}

XInputMethod* XInputMethod::instance()
{
    if (NULL == XInputMethodPrivate::pInputMethod)
    {
        XInputMethodPrivate::pInputMethod = new XInputMethod();
    }
    
    return XInputMethodPrivate::pInputMethod;
}

XInputMethod::XInputMethod(): mpdata(new XInputMethodPrivate)
{
    mpdata->pframe = new XWindow(mpdata->imedata);
}

XInputMethod::~XInputMethod()
{
    if (mpdata)
    {
        delete mpdata->pframe;
        delete mpdata;
        mpdata = NULL;
    }
}

bool XInputMethod::filter(int /*unicode*/, int keycode, int modifiers,
                                bool isPress, bool /*autoRepeat*/)
{
    if (isPress && (Qt::AltModifier & modifiers) && (Qt::Key_Z == keycode))
    {
        toggleIME();

        return true;
    }


    if (mpdata && mpdata->pframe && mpdata->pframe->isVisible() && isPress)
    {
        if ((Qt::Key_A <= keycode) && (Qt::Key_Z >= keycode))
        {
            char ch = (char)((Qt::ShiftModifier & modifiers) ? 
                             keycode : (keycode - Qt::Key_A + 'a'));

            newCharacter(ch);

            return true;
        }

        if ((Qt::Key_0 <= keycode) && (Qt::Key_9 >= keycode))
        {
            return makeSelection(keycode - Qt::Key_0);
        }

        if (Qt::Key_PageDown == keycode)
        {
            showNextPage();
            return true;
        }

        if (Qt::Key_PageUp == keycode)
        {
            showPreviousPage();
            return true;
        }
    }

    return false;
}


void XInputMethod::toggleIME()
{
    if (mpdata->pframe->isVisible())
    {
        mpdata->pframe->hide();
        mpdata->imedata.reset();
    }
    else
    {
        mpdata->pframe->show();
    }
}


void XInputMethod::newCharacter(char ch)
{
    mpdata->imedata.strPinyin += ch;

    mpdata->imedata.listHanzi << "a";
    mpdata->imedata.listHanzi << "b";
    mpdata->imedata.listHanzi << "c";
    mpdata->imedata.listHanzi << "d";
    mpdata->imedata.listHanzi << "e";
    mpdata->imedata.listHanzi << "f";
    mpdata->imedata.listHanzi << "g";
    mpdata->imedata.listHanzi << "h";
    mpdata->imedata.listHanzi << "i";
    mpdata->imedata.listHanzi << "j";
    mpdata->imedata.listHanzi << "k";
    mpdata->imedata.listHanzi << "l";
    mpdata->imedata.listHanzi << "m";
    mpdata->imedata.listHanzi << "n";
    mpdata->imedata.listHanzi << "o";
    mpdata->imedata.listHanzi << "p";
    mpdata->imedata.listHanzi << "q";
    mpdata->imedata.listHanzi << "r";
    mpdata->imedata.listHanzi << "s";
    mpdata->imedata.listHanzi << "t";
    mpdata->imedata.listHanzi << "u";
    mpdata->imedata.listHanzi << "v";
    mpdata->imedata.listHanzi << "w";
    mpdata->imedata.listHanzi << "x";
    mpdata->imedata.listHanzi << "y";
    mpdata->imedata.listHanzi << "z";

    mpdata->pframe->update();
}

bool XInputMethod::makeSelection(int number)
{
    number--;

    if ((mpdata->imedata.first_visible + number) < mpdata->imedata.listHanzi.count())
    {
        QString result = mpdata->imedata.listHanzi[mpdata->imedata.first_visible + number];

        if (!result.isEmpty())
        {
            sendCommitString(result);
            mpdata->imedata.reset();
            mpdata->pframe->update();

            return true;
        }
    }

    return false;
}


void XInputMethod::showNextPage()
{
    if ((mpdata->imedata.first_visible + mpdata->imedata.counts_per_page) < mpdata->imedata.listHanzi.count())
    {
        mpdata->imedata.first_visible += mpdata->imedata.counts_per_page;
        mpdata->pframe->update();
    }
}

void XInputMethod::showPreviousPage()
{
    if ((mpdata->imedata.first_visible - mpdata->imedata.counts_per_page) >= 0)
    {
        mpdata->imedata.first_visible -= mpdata->imedata.counts_per_page;
        mpdata->pframe->update();
    }
}


