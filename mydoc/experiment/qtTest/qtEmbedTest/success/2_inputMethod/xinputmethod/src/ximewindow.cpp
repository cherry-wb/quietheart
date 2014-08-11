#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QPushButton>
#include <QStringList>

#include "ximewindow.h"



#include "ximedata.h"      

struct XWindowPrivate
{
	//用户输入和处理后的输出
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

	//获得结果列表和列表长度
    const QStringList& listHz = mpdata->imedata.listHanzi;
    const int listCounts = listHz.count();

    if ((0 == listCounts) ||
        (mpdata->imedata.first_visible >= listCounts) )
        return; 


	//将结果字符串绘制
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

