
/*
	Author: shiroki@www.cuteqt.com
	License: GPLv2
*/

#include "inputwidget.h"
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <Q3HBoxLayout>
#include <QWSInputMethod>
#include <QSignalMapper>
//Added by qt3to4:
#include <Q3VBoxLayout>

InputWidget::InputWidget(QWSInputMethod* im)
:QWidget(0
, Qt::Tool| Qt::WindowStaysOnTopHint //) 
| Qt::FramelessWindowHint)
{
	setWindowTitle("www.cuteqt.com");
	setFocusPolicy(Qt::NoFocus);

	QPalette pal = palette();
	pal.setColor(QPalette::Background, QColor(12,15,0));
	setPalette(pal);

	Q3VBoxLayout* alllayout = new Q3VBoxLayout(this);
	Q3HBoxLayout* layout = new Q3HBoxLayout;
	alllayout->addLayout(layout);

        QSignalMapper* mapper = new QSignalMapper(this);
        connect(mapper, SIGNAL(mapped(const QString&)), im, SLOT(sendContent(const QString&)));

	QPushButton* btn = new QPushButton("A");
        mapper->setMapping(btn, "A");
	connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));
	layout->addWidget(btn);
	
	btn = new QPushButton("B");
        mapper->setMapping(btn, "B");
	connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));
	layout->addWidget(btn);
	btn = new QPushButton("C");
        mapper->setMapping(btn, "C");
	connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));
	layout->addWidget(btn);
	btn = new QPushButton("D");
        mapper->setMapping(btn, "D");
	connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));
	layout->addWidget(btn);

	btn = new QPushButton("Confirm");
	connect(btn, SIGNAL(clicked()), im, SLOT(confirmContent()));
	alllayout->addWidget(btn);

}

InputWidget::~InputWidget()
{
}

