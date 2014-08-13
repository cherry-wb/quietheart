#include <QScrollArea>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QLCDNumber>
#include <QDebug>
#include "myCallback.h"

MyCallback::MyCallback(QWidget *parent,Qt::WindowFlags f):QWidget(parent,f)
{
	m_timerCnt = 0;
	m_recordCnt = 0;
	m_timer = new QTimer(this);
	QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));

	QVBoxLayout *gvbox = new QVBoxLayout(this);

	//time display
	m_display = new QLCDNumber();
	m_display->display("00:00:00");
	gvbox->addWidget(m_display);

	//records
	m_sa = new QScrollArea;
	//m_sa->setWidgetResizable(true);
	createTimeList();
	gvbox->addWidget(m_sa);
	
	//control buttons
	QHBoxLayout *btnh = new QHBoxLayout;
	gvbox->addLayout(btnh);

	m_recordBtn = new QPushButton("Start");
	QObject::connect(m_recordBtn, SIGNAL(clicked()), this, SLOT(timeRecord()));
	btnh->addWidget(m_recordBtn);

	m_pauseBtn = new QPushButton("Pause");
	QObject::connect(m_pauseBtn, SIGNAL(clicked()), this, SLOT(timePause()));
	btnh->addWidget(m_pauseBtn);

	m_clearBtn = new QPushButton("Clear");
	QObject::connect(m_clearBtn, SIGNAL(clicked()), this, SLOT(timeClear()));
	btnh->addWidget(m_clearBtn);
}

void MyCallback::createTimeList(void)
{
	m_saWidget = new QWidget;
	m_saVbox = new QVBoxLayout(m_saWidget);
	QLabel *label = new QLabel("00:00");
	m_recordCnt = 1;
	m_saVbox->addWidget(label);
	m_sa->setWidget(m_saWidget);
	m_saWidget->show();
}

void MyCallback::timeUpdate(void)
{
	++m_timerCnt;
	m_display->display(QString("%1:").arg(m_timerCnt/100,2,10,QChar('0'))
				+QString("%1").arg(m_timerCnt%100,2,10,QChar('0')));
}

void MyCallback::timeRecord(void)
{
	if(m_recordBtn->text() == "Start")
	{
		m_timer->start(10);//10毫秒精度
		m_recordBtn->setText("Record");
	}
	else
	{
		QString record(QString("%1:").arg(m_timerCnt/100,2,10,QChar('0'))
					+QString("%1").arg(m_timerCnt%100,2,10,QChar('0')));
		QLabel *label = new QLabel(record);

		m_saVbox->addWidget(label);
		++m_recordCnt;
		m_saWidget->resize(m_saWidget->width(),m_saWidget->height() + m_saWidget->height()/m_recordCnt);
		//m_saWidget->scroll(0,0);
	}
}

void MyCallback::timePause(void)
{
	if(m_recordBtn->text() == "Record")
	{
		m_timer->stop();
		m_recordBtn->setText("Start");
	}
}

void MyCallback::timeClear(void)
{
	timePause();
	if(m_recordCnt > 1)
	{
		m_timerCnt = 0;
		m_display->display("00:00:00");
		createTimeList();
	}
}
