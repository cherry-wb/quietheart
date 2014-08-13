/*
	Author: shiroki@www.cuteqt.com
	License: GPLv2
*/

#ifndef IMFRAME_H
#define IMFRAME_H

#include <QWSInputMethod>
#include <QStringList>

class InputWidget;
enum IM_STATE
{
	KEY_BOARD,
	HAND_WRITE
};
class IMFrame:public QWSInputMethod
{
Q_OBJECT
public:
	IMFrame();
	~IMFrame();
    virtual bool filter(int unicode, int keycode, int modifiers,
                        bool isPress, bool autoRepeat);
	//过滤鼠标事件
	virtual bool filter(const QPoint & position, int state,
			int wheel);
	void setMicroFocus(int, int);
	//焦点进入进出的时候
	void updateHandler(int);

public:
	int getCurPg();
	QStringList& getResultList();

private:
	//用户操作界面，显示输入按钮以及发送相应消息
	InputWidget* inputwidget;
	
	//存放在输入法上下文中的字符（处理过之后的？）
	QString content;
	//当前选择的输入法
	IM_STATE state;

	//处理前的输入
	QString strPinyin;

	//处理的结果列表
	QStringList listResult;

	//存放用户输入，处理用户输入得到用户输出，保存输出结果
	void processCharacter(char);

	//如果存在多个结果，存放当前的页
	int cur_pg;
private slots:
	//将内容通过这个函数发送到输入法上下文中
	void sendContent(const QString& newContent);

	void sendKeyBoardContent(const QString &key);
	//将输入法上下文中的字符确实的发送到编辑框中
	void confirmContent();
};

#endif
