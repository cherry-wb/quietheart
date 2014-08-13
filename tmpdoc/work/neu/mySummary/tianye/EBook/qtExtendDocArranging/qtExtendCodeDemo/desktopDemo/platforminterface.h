/****************************************************************************
**
** This file is part of the Qt Extended Opensource Package.
**
** Copyright (C) 2009 Trolltech ASA.
**
** Contact: Qt Extended Information (info@qtextended.org)
**
** This file may be used under the terms of the GNU General Public License
** version 2.0 as published by the Free Software Foundation and appearing
** in the file LICENSE.GPL included in the packaging of this file.
**
** Please review the following information to ensure GNU General Public
** Licensing requirements will be met:
**     http://www.fsf.org/licensing/licenses/info/GPLv2.html.
**
**
****************************************************************************/
#ifndef PLATFORMINTERFACE_H
#define PLATFORMINTERFACE_H

#include "qabstractserverinterface.h"

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>
#include <QVBoxLayout>

//==============================================================================
// HomeButton
//==============================================================================
class HomeButton : public QWidget
{
    Q_OBJECT;
public:
    HomeButton(QWidget *parent = 0, const QString & iconpath = QString(),
    		 const QString & text = QString())
        : QWidget(parent)
        , m_iconLabel(0)
        , m_titleLabel(0)
        , m_textLabel(0)
    {
        m_iconLabel = new QLabel(this);
        m_iconLabel->setAlignment(Qt::AlignCenter);
        m_iconLabel->setFixedSize(0, 0);
        m_titleLabel = new QLabel(this);
        m_titleLabel->setAlignment(Qt::AlignCenter);
        m_titleLabel->setFixedSize(0, 0);
        m_textLabel = new QLabel(this);
        m_textLabel->setAlignment(Qt::AlignCenter);
        m_textLabel->setFixedSize(0, 0);
        
        setLayout(new QVBoxLayout(this));
        layout()->setAlignment(Qt::AlignCenter);
        layout()->setContentsMargins(0,0,0,0);
        layout()->setSpacing(0);
        
        layout()->addWidget(m_iconLabel);
        layout()->addWidget(m_titleLabel);
        layout()->addWidget(m_textLabel);

        if(!text.isEmpty()) { setTitle(text); }
        if(!iconpath.isEmpty()) { setIcon(iconpath); }
    }

    virtual ~HomeButton(){};

    void confirmFixedSize()
    {
        m_titleLabel->setFixedWidth(m_iconLabel->minimumWidth());
        m_textLabel->setFixedWidth(m_iconLabel->minimumWidth());
        int heightsum = (m_iconLabel->height())
                   + (m_titleLabel->text().isEmpty() ? 0 : m_titleLabel->height())
                   + (m_textLabel->text().isEmpty() ? 0 : m_textLabel->height());
        setFixedSize(QSize(m_iconLabel->width(),heightsum));
    }

    void setIcon(const QString & iconpath)
    {
        QPixmap pixicon(iconpath);
        QSize sizepix = pixicon.size();
        m_iconLabel->setPixmap(pixicon);
        m_iconLabel->setFixedSize(sizepix);
        confirmFixedSize();
    }

    void setTitle(const QString & title, const QFont * pFont = NULL)
    {
        if(pFont) { m_titleLabel->setFont(*pFont); }
        m_titleLabel->setText(title);
        QRect rect = QFontMetrics(m_titleLabel->font()).boundingRect(title);
        m_titleLabel->setFixedHeight(rect.height());
        confirmFixedSize();
    }

    void setText(const QString & text, const QFont * pFont = NULL)
    {
        if(pFont) { m_textLabel->setFont(*pFont); }
        m_textLabel->setText(text);
        QRect rect = QFontMetrics(m_textLabel->font()).boundingRect(text);
        m_textLabel->setFixedHeight(rect.height());
        confirmFixedSize();
    }

    void setEntry(const QString & strLink, const QStringList & args = QStringList())
    {
        m_entry = strLink;
        m_args = args;
    }

    const QString & entry() { return m_entry; }
    
protected:
    void mouseReleaseEvent(QMouseEvent *event)
    {
        if(rect().contains(event->pos())) { emit clicked(m_entry,m_args); }
    }

signals:
    void clicked(const QString & entry, const QStringList & args);

private:
    QLabel  *m_iconLabel;
    QLabel  *m_titleLabel;
    QLabel  *m_textLabel;
    QString     m_entry;
    QStringList m_args;
};

//==============================================================================
// PlatformServerInterface
//==============================================================================
class QAbstractHeader;
class QAbstractContextLabel;
class QStackedWidget;
class QContent;
class QLineEdit;
class QListWidget;
class QListWidgetItem;
class PlatformServerInterface : public QAbstractServerInterface
{
    Q_OBJECT;
public:
    PlatformServerInterface(QWidget* parent = 0, Qt::WFlags flags = 0);
    ~PlatformServerInterface();

protected:
    virtual void showEvent(QShowEvent * event);
    virtual void keyPressEvent(QKeyEvent * event);
    
private slots:
    void execContent(const QContent & content);
    void launchApp(const QString & entry, const QStringList & args);
    void onSettingList(QListWidgetItem *item);
    void actionClicked(const QString &act);

private:
    void initDesktop();
    void defaultButtons();
    void createButtons();
    void showSearchFrame();
    void OnDocumentSearchClicked();
    void OnMp3SearchClicked();

private:
    QAbstractHeader         *m_header;
    QAbstractContextLabel   *m_context;
    QStackedWidget          *m_stack;
    QWidget                 *m_desktop;
    QList<HomeButton*>      m_btnList;

    QWidget *m_setting_container;
    QListWidget *m_setting_list;

    QWidget *searchWindow;
    QLineEdit *searchLine;
};

#endif
