#include "popupim.h"
#include <QGridLayout>

PopupIM::PopupIM(QWidget *parent, const char *name, Qt::WindowFlags flags)
: QWidget(parent, flags)
{
	//创建一个键盘布局
	QGridLayout *gl = new QGridLayout(this);

	PopupPushButton *ppb;

	//每个按钮构造指明按钮显示值，点击按钮映射的键盘键，以及父窗口
	ppb = new PopupPushButton(QChar('0'), Qt::Key_0, this);
	//按下按钮，按钮的自定义keyPress信号发出，后立即传递给输入的keyPress信号
	connect(ppb, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
			this, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)));
	gl->addWidget(ppb, 0, 0);
	ppb = new PopupPushButton(QChar('1'), Qt::Key_1, this);
	connect(ppb, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
			this, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)));
	gl->addWidget(ppb, 0, 1);
	ppb = new PopupPushButton(QChar('2'), Qt::Key_2, this);
	connect(ppb, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
			this, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)));
	gl->addWidget(ppb, 0, 2);
	ppb = new PopupPushButton(QChar('3'), Qt::Key_3, this);
	connect(ppb, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
			this, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)));
	gl->addWidget(ppb, 0, 3);
	ppb = new PopupPushButton(QChar('4'), Qt::Key_4, this);
	connect(ppb, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
			this, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)));
	gl->addWidget(ppb, 0, 4);
	ppb = new PopupPushButton(QChar('5'), Qt::Key_5, this);
	connect(ppb, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
			this, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)));
	gl->addWidget(ppb, 1, 0);
	ppb = new PopupPushButton(QChar('6'), Qt::Key_6, this);
	connect(ppb, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
			this, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)));
	gl->addWidget(ppb, 1, 1);
	ppb = new PopupPushButton(QChar('7'), Qt::Key_7, this);
	connect(ppb, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
			this, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)));
	gl->addWidget(ppb, 1, 2);
	ppb = new PopupPushButton(QChar('8'), Qt::Key_8, this);
	connect(ppb, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
			this, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)));
	gl->addWidget(ppb, 1, 3);
	ppb = new PopupPushButton(QChar('9'), Qt::Key_9, this);
	connect(ppb, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
			this, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)));
	gl->addWidget(ppb, 1, 4);
	ppb = new PopupPushButton(QChar('A'), Qt::Key_A, this);
	connect(ppb, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
			this, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)));
	gl->addWidget(ppb, 2, 0);
	ppb = new PopupPushButton(QChar('B'), Qt::Key_B, this);
	connect(ppb, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
			this, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)));
	gl->addWidget(ppb, 2, 1);
	ppb = new PopupPushButton(QChar('C'), Qt::Key_C, this);
	connect(ppb, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
			this, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)));
	gl->addWidget(ppb, 2, 2);
	ppb = new PopupPushButton(QChar('D'), Qt::Key_D, this);
	connect(ppb, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
			this, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)));
	gl->addWidget(ppb, 2, 3);
	ppb = new PopupPushButton(QChar('E'), Qt::Key_E, this);
	connect(ppb, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
			this, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)));
	gl->addWidget(ppb, 2, 4);
	ppb = new PopupPushButton(QChar('F'), Qt::Key_E, this);
	connect(ppb, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
			this, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)));
	gl->addWidget(ppb, 3, 0);

	ppb = new PopupPushButton("Back", Qt::Key_Backspace, this);
	connect(ppb, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
			this, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)));
	//gl->addMultiCellWidget(ppb, 3, 3, 1, 4);
	gl->addWidget(ppb, 3, 1);
}

PopupIM::~PopupIM()
{
}
