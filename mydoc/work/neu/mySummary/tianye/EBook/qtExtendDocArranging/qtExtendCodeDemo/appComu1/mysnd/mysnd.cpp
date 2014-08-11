#include "mysnd.h"
#include <qsoftmenubar.h>
#include <QKeyEvent>
#include <QPushButton>
#include <QtDebug>
#include <QtopiaApplication>

#include <QCopChannel>
#ifdef Q_WS_QWS
#include <qwindowsystem_qws.h>
#endif

MySnd::MySnd(QWidget *parent, Qt::WFlags f)
    : QWidget(parent, f)
{
    QPushButton *btn = new QPushButton("Send", this);
    connect(btn, SIGNAL(clicked()), this, SLOT(clickResp()));
    QMenu *menu = QSoftMenuBar::menuFor(this);

    // Normally, we would use "menu" to add more actions.
    // The context menu will not be active unless it has at least one action.
    // Tell Qtopia to provide the "Help" option, which will enable the user to
    // read the Help documentation for this application.
    //QSoftMenuBar::setHelpEnabled(this,true);
    Q_UNUSED(menu);
}

MySnd::~MySnd()
{
}

void MySnd::keyPressEvent(QKeyEvent * event)
{
	qDebug()<<"key pressed in myexample!";
	if(event->key() == Qt::Key_Home)
	{
		qDebug()<<"home key pressed";
	}
	event->ignore();
}
void MySnd::clickResp()
{
	qDebug()<<"click to send message from mysnd to myrcv";
	//message
	QString message ="home()";

	//param for message(option)
	QByteArray data;
	//QDataStream stream(&data, QIODevice::ReadWrite|QIODevice::Unbuffered);
	QDataStream stream(&data, QIODevice::WriteOnly);
	stream << QString(QtopiaApplication::instance()->applicationName());

	qDebug()<<"the message name is"<<message;
	//qDebug()<<"the param of message is"<<data;

	//send
	QCopChannel::send("/MyApp/myrcv", message, data);
	QCopChannel::flush();//ensure send the message immediately
}
