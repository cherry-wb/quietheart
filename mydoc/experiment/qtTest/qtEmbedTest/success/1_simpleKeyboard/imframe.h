/*
	Author: shiroki@www.cuteqt.com
	License: GPLv2
*/

#ifndef IMFRAME_H
#define IMFRAME_H

#include <QWSInputMethod>

class InputWidget;
class IMFrame:public QWSInputMethod
{
Q_OBJECT
public:
	IMFrame();
	~IMFrame();
	void setMicroFocus(int, int);
	//焦点进入进出的时候
	void updateHandler(int);

private:
	//用户操作界面，显示输入按钮以及发送相应消息
	InputWidget* inputwidget;
	//存放在输入法上下文中的字符（处理过之后的？）
	QString content;

private slots:
	//将内容通过这个函数发送到输入法上下文中
	void sendContent(const QString& newContent);
	//将输入法上下文中的字符确实的发送到编辑框中
	void confirmContent();
};

#endif
