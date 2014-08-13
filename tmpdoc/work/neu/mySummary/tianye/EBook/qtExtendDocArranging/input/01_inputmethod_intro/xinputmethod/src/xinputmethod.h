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


#ifndef _XINPUTMETHOD_8c8c9d7c8d7c9as678xc_
#define _XINPUTMETHOD_8c8c9d7c8d7c9as678xc_

#include <QWSInputMethod>



struct XInputMethodPrivate;

class XInputMethod : public QWSInputMethod
{
    Q_OBJECT

public:

    static void installInputMethod();
    static void releaseInputMethod();
    static XInputMethod* instance();

    virtual bool filter(int unicode, int keycode, int modifiers,
                        bool isPress, bool autoRepeat);

    virtual ~XInputMethod();

private:
    XInputMethod();
	
  
    void toggleIME();

    void newCharacter(char);
    bool makeSelection(int);
    void showNextPage();
    void showPreviousPage();

    XInputMethodPrivate* mpdata;
};



//-------------------------------------------------------
#endif //_XINPUTMETHOD_8c8c9d7c8d7c9as678xc_
