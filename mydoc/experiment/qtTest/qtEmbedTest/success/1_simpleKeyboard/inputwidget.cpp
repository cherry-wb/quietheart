#include "inputwidget.h"
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWSInputMethod>
#include <QSignalMapper>

InputWidget::InputWidget(QWSInputMethod* im)
:QWidget(0
, Qt::Tool| Qt::WindowStaysOnTopHint //) 
| Qt::FramelessWindowHint)
{//这里创建输入法用户输入界面
	//这里构造函数的最后一个参数flag是位或,通常默认为0
	//Qt::Tool表示是一个工具窗口，通常在父亲的顶部
	//Qt::WindowStaysOnTopHint，指明该窗口在所有窗口的顶部(不被阻挡)
	//Qt::FramelessWindowHint,没有边框的窗口，无法移动(好像去掉这个也不支持移动)
	setWindowTitle("www.cuteqt.com");
	setFocusPolicy(Qt::NoFocus);

	QPalette pal = palette();
	pal.setColor(QPalette::Background, QColor(12,15,0));
	setPalette(pal);

	QVBoxLayout* alllayout = new QVBoxLayout(this);
	QHBoxLayout* layout = new QHBoxLayout;
	alllayout->addLayout(layout);

	//类似桥梁的信号中转
	//即"发送者构件signal-->QSignalMapper的map槽(该槽发送信号mapped),
	//QsignalMapper的mapped信号--->接收者构件slot"
	QSignalMapper* mapper = new QSignalMapper(this);
	//接收的信号通过（mapped）中转，连接到槽sendContent上.
	connect(mapper, SIGNAL(mapped(const QString&)), im, SLOT(sendContent(const QString&)));

	///////创建输入按钮
	QPushButton* btn = new QPushButton("A");
	//这里设置发送者中转信号时发送一个"A"给mapper,
	//这样点击的click虽然没有参数但是却发送了一个"A",后面类似.
	mapper->setMapping(btn, "A");
	//点击调用map槽（该槽发送mapped信号）
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

