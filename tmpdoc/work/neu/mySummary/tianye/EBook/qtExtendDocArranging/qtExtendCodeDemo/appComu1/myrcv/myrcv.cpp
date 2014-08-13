#include "myrcv.h"
#include <qsoftmenubar.h>
#include <QKeyEvent>
#include <QLabel>
#include <QtDebug>
#include <QCopChannel>

#ifdef Q_WS_QWS
#include <qwindowsystem_qws.h>
#endif

MyRcv::MyRcv(QWidget *parent, Qt::WFlags f)
    : QWidget(parent, f)
{
    new QLabel("My Receive", this);
    QMenu *menu = QSoftMenuBar::menuFor(this);

    // Normally, we would use "menu" to add more actions.
    // The context menu will not be active unless it has at least one action.
    // Tell Qtopia to provide the "Help" option, which will enable the user to
    // read the Help documentation for this application.
    //QSoftMenuBar::setHelpEnabled(this,true);
    Q_UNUSED(menu);
    //create a channel from receive messages
    channel = new QCopChannel("/MyApp/myrcv", this );
    connect(channel, SIGNAL(received(const QString&,const QByteArray&)),
		    this, SLOT(processRcv(const QString&,const QByteArray&)) );
}

MyRcv::~MyRcv()
{
}

void MyRcv::keyPressEvent(QKeyEvent * event)
{
	qDebug()<<"key pressed in myexample!";
	if(event->key() == Qt::Key_Home)
	{
		qDebug()<<"home key pressed";
	}
	event->ignore();
}
void MyRcv::processRcv(const QString &msg, const QByteArray &data)
{
	qDebug()<<"receive message in myrcv from the mysnd application.";
	QDataStream stream( data );
	QString param;
	stream>>param;
	qDebug()<<"message name is:"<<msg;
	qDebug()<<"message param is:"<<param;
}
