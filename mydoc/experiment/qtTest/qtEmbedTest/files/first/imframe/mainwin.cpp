
/*
	Author: shiroki@www.cuteqt.com
	License: GPLv2
*/

#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QWSServer>
#include "mainwin.h"
#include "imframe.h"

MainWin::MainWin(QWidget*p, Qt::WindowFlags f)
:QWidget(p,f)
{
	setWindowTitle("www.cuteqt.com");


	QVBoxLayout* layout = new QVBoxLayout(this);

	QLabel* label = new QLabel;
	label->setText("<a href=\"www.cuteqt.com\"><font color=#008800>www.cuteqt.com</font></a>");
	layout->addWidget(label);

	le = new QLineEdit;
	layout->addWidget(le);

	QPushButton* btn = new QPushButton("Clear");
	connect(btn, SIGNAL(clicked()), this, SLOT(clear()));
	layout->addWidget(btn);
	btn = new QPushButton("Quit");
	connect(btn, SIGNAL(clicked()), qApp, SLOT(quit()));
	layout->addWidget(btn);
	
	QWSInputMethod* im = new IMFrame;
	QWSServer::setCurrentInputMethod(im);	

}

MainWin::~MainWin()
{
}

void MainWin::clear()
{
	le->clear();
}
