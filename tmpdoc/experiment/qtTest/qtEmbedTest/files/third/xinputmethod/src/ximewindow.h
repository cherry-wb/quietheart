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


#ifndef _XIMEWINDOW_H_7c8d7829c7s6c8_
#define _XIMEWINDOW_H_7c8d7829c7s6c8_


#include <QWidget>





struct XData;
struct XWindowPrivate;


class XWindow : public QWidget
{
    Q_OBJECT

public:
    XWindow(const XData&, QWidget* parent = 0);
    virtual ~XWindow();


protected:
    virtual void paintEvent(QPaintEvent*);

private:
    void layout();

private:
    XWindowPrivate* mpdata;
};

//-------------------------------------------------------
#endif // _XIMEWINDOW_H_7c8d7829c7s6c8_
