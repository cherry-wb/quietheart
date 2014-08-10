#include "myCallback.h"
#include <QDebug>
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	m_label = new EPushLabel("click here!",this);
	connect(m_label,SIGNAL(pressSignal()),this,SLOT(labelPush()));
}
void MyCallback::labelPush()
{
	qDebug()<<"clicked!";
}
EPushLabel::EPushLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
:QLabel(text, parent, f)
{   
	;   
}   
void EPushLabel::mousePressEvent(QMouseEvent *event)
{   
	if(rect().contains(event->pos())) { emit pressSignal(); }
}   
