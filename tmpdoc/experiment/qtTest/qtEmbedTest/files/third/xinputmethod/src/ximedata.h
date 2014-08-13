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


#ifndef _X_DATA_H_ICODIC8E0C87S9C7_
#define _X_DATA_H_ICODIC8E0C87S9C7_


#define COUNTS_PER_PAGE 9


struct XData
{
    QString strPinyin;
    QStringList listHanzi;

    int counts_per_page;

    int first_visible;

    XData() :
        counts_per_page(COUNTS_PER_PAGE),
        first_visible(0)
    {}


    void reset()
    {
        strPinyin = "";
        listHanzi.clear();
        first_visible = 0;
    }
};




//------------------------------------------------------
#endif //_X_DATA_H_ICODIC8E0C87S9C7_
