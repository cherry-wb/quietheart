#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
class QLineEdit;
class QWSInputMethod;
class InputWidget:public QWidget
{
Q_OBJECT
public:
	InputWidget(QWSInputMethod* im);
	~InputWidget();
private slots:

private:
};

#endif
