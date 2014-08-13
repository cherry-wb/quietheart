#include "popupim.h"
#include <qpushbutton.h>
#include <qlayout.h>

/*
   A virtual key for a virtual keyboard
*/
class PopupPushButton : public QPushButton
{
    Q_OBJECT
public:
    PopupPushButton ( const QChar uni, ushort key, QWidget *parent )
	: QPushButton(parent), u(uni), k(key)
    {
	connect(this, SIGNAL(pressed()), this, SLOT(sendKeyForPress()));
	connect(this, SIGNAL(released()), this, SLOT(sendKeyForRelease()));
	setText(QChar(uni));
    }
    PopupPushButton ( const QString &text, ushort key, QWidget *parent )
	: QPushButton(parent), u(0xffff), k(key)
    {
	connect(this, SIGNAL(pressed()), this, SLOT(sendKeyForPress()));
	connect(this, SIGNAL(released()), this, SLOT(sendKeyForRelease()));
	setText(text);
    }
signals:
	//信号是发送出去的，所以一般发送给外部不会自己接受自己的信号
    void keyPress(ushort, ushort, ushort, bool, bool);

private slots:
    void sendKeyForPress()
    {
	emit keyPress(u.unicode(), k, 0, TRUE, FALSE);
    }
    void sendKeyForRelease()
    {
	emit keyPress(u.unicode(), k, 0, FALSE, FALSE);
    }
private:
    QChar u;
    ushort k;
};

PopupIM::PopupIM(QWidget *parent, const char *name, int flags)
    : QWidget(parent, name, flags)
{
    // create a layout
    QGridLayout *gl = new QGridLayout(this, 5,3);
    PopupPushButton *ppb;

    // create virtual keys and add to virtual layout
    ppb = new PopupPushButton(QChar('0'), Qt::Key_0, this);
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
    gl->addMultiCellWidget(ppb, 3, 3, 1, 4);
}

PopupIM::~PopupIM()
{
}

#include "popupim.moc"
