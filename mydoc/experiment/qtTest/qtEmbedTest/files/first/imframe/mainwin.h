/*
	Author: shiroki@www.cuteqt.com
	License: GPLv2
*/

#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
class QLineEdit;
class MainWin:public QWidget
{
Q_OBJECT
public:
	MainWin(QWidget*p = NULL, Qt::WindowFlags f = 0);
	~MainWin();
private slots:
	void clear();

private:
	QLineEdit* le;
};

#endif
