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
#include <QDesktopWidget>
#include <QPainter>
#include <QPushButton>
#include <QStringList>

#include "ximewindow.h"



#include "ximedata.h"      

struct XWindowPrivate
{
    const XData& imedata;

    XWindowPrivate(const XData& i)
        : imedata(i)
    {}
};



#define IME_WND_FLAG (Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool)


XWindow::XWindow(const XData& idata, QWidget* parent)
    : QWidget(parent, IME_WND_FLAG), mpdata(new XWindowPrivate(idata))
{
    layout();
}

XWindow::~XWindow()
{
    delete mpdata;
}

void XWindow::layout()
{
    QSize size(320, 240);
    QDesktopWidget* pdw = QApplication::desktop();
    if (pdw)
    {
        size = pdw->screenGeometry(0).size();
    }

    const int nheight = 60;

    move(0, size.height() - nheight);
    resize(size.width(), nheight);
}

void XWindow::paintEvent(QPaintEvent* e)
{
    QWidget::paintEvent(e);

    const QStringList& listHz = mpdata->imedata.listHanzi;
    const int listCounts = listHz.count();

    if ((0 == listCounts) ||
        (mpdata->imedata.first_visible >= listCounts) )
        return; 


    QPainter painter(this);

    painter.drawText(2, 10, mpdata->imedata.strPinyin);

    const int lastLoopIndex = 
        ((mpdata->imedata.first_visible + mpdata->imedata.counts_per_page) < listCounts)
        ? (mpdata->imedata.first_visible + mpdata->imedata.counts_per_page)
        : (listCounts);

    QString hanzi;
    for (int i = mpdata->imedata.first_visible; i < lastLoopIndex; i++)
    {
        const QString& hz = listHz[i];
        if (hz.isEmpty()) continue;

        hanzi += QString(" %1%2").arg(i - mpdata->imedata.first_visible + 1).arg(hz);
    }

    if (!hanzi.isEmpty())
        painter.drawText(0, 30, hanzi);
}

