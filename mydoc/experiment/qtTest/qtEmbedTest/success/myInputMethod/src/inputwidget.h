#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include <QLabel>
#include "mySelectList.h"

//每页显示的选项数目
//#define PAGECOUNT 6
#define KEYBOARD_METHOD 0
#define PINYIN_METHOD 1
#define HANDWRITE_METHOD 2
class QLineEdit;
class QWSInputMethod;
class QStackedLayout;
class QVBoxLayout;
class InputWidget:public QWidget /*public QDesktopWidget*/
{
Q_OBJECT
public:
	InputWidget(QWSInputMethod* im);
	~InputWidget();
	void createKeyboard();
	void createPinyinTable();
	void createHandWrite();
	void setMethodWidget(int select);
	void pinyin_refresh();
private slots:

public:
	QWSInputMethod* im;
	int cnt_per_pg;
	int select;

	QVBoxLayout *allLay;
	QStackedLayout *lay;

	//键盘
	QWidget *keyboard;

	//显示待选择结果的列表
	//QLabel *pinyinTable;
	MySelectList *pinyinTable;

	QWidget *handwrite;

};

#endif
