#include "myapp.h"
#include <qsoftmenubar.h>
#include <QKeyEvent>
#include <QLabel>
#include <QtDebug>

#ifdef Q_WS_QWS
#include <qwindowsystem_qws.h>
#endif

MyApp::MyApp(QWidget *parent, Qt::WFlags f)
    : QWidget(parent, f)
{
    new QLabel("My Application", this);
    QMenu *menu = QSoftMenuBar::menuFor(this);

    // Normally, we would use "menu" to add more actions.
    // The context menu will not be active unless it has at least one action.
    // Tell Qtopia to provide the "Help" option, which will enable the user to
    // read the Help documentation for this application.
    //QSoftMenuBar::setHelpEnabled(this,true);
    Q_UNUSED(menu);
}

MyApp::~MyApp()
{
}

void MyApp::keyPressEvent(QKeyEvent * event)
{
	qDebug()<<"key pressed in myexample!";
	if(event->key() == Qt::Key_Home)
	{
		qDebug()<<"home key pressed";
	}
	event->ignore();
}
