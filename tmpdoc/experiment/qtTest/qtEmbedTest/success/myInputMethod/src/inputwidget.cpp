#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWSInputMethod>
#include <QSignalMapper>
#include <QStackedLayout>
#include <QtUiTools>
#include <QSize>
#include <QDesktopWidget>
#include <QTextCodec>
#include <iostream>
#include "inputwidget.h"
#include "imframe.h"

using std::cout;
using std::endl;

InputWidget::InputWidget(QWSInputMethod* im)
:QWidget(0
, Qt::Tool| Qt::WindowStaysOnTopHint //) 
| Qt::FramelessWindowHint)
{//这里创建输入法用户输入界面
	//这里构造函数的最后一个参数flag是位或,通常默认为0
	//Qt::Tool表示是一个工具窗口，通常在父亲的顶部
	//Qt::WindowStaysOnTopHint，指明该窗口在所有窗口的顶部(不被阻挡)
	//Qt::FramelessWindowHint,没有边框的窗口，无法移动(好像去掉这个也不支持移动)
	this->im = im;
	keyboard = NULL;
	handwrite = NULL;
	pinyinTable = NULL;
	cnt_per_pg = PAGECOUNT;
	//setWindowTitle("www.cuteqt.com");
	setFocusPolicy(Qt::NoFocus);
	setWindowOpacity(0.5);


	QPalette pal = palette();
	pal.setColor(QPalette::Background, QColor(255,255,255));
	setPalette(pal);

	//设置大小和位置
	QSize size(320, 240);
	QDesktopWidget* pdw = QApplication::desktop();
	if(pdw)
	{
		size = pdw->screenGeometry(0).size();
	}
	//int nheight = 60;
	move(0, size.height()>>1);
	resize(size.width(), size.height()>>1);

	allLay = new QVBoxLayout(this);
	this->setLayout(allLay);

	lay = new QStackedLayout;

	createKeyboard();
	createHandWrite();
	lay->addWidget(keyboard);
	//keyboard->move(size.width()>>1,size.height()>>1);
	lay->addWidget(handwrite);

	createPinyinTable();
	allLay->addWidget(pinyinTable);

	allLay->addLayout(lay);
	//默认使用软键盘的外观,0
	//pinyinTable = new QLabel("testtttttttttttttt");
	//pinyinTable = new MySelectList();
	//pinyinTable->hide();
	select = KEYBOARD_METHOD;
	//select = PINYIN_METHOD;
	//setMethodWidget(KEYBOARD_METHOD);
	setMethodWidget(select);
	//setMethodWidget(1);

}

void InputWidget::createKeyboard()
{
	if(keyboard == NULL)
	{
		//加载ui文件
		QUiLoader loader;
		QFile file("./cfg/myKeyBoard.ui");
		file.open(QFile::ReadOnly);
		keyboard = loader.load(&file); 
		file.close();

//		keyboard->show();

		//添加键映射
		QSignalMapper* mapper = new QSignalMapper(this);
		connect(mapper, SIGNAL(mapped(const QString&)), im, SLOT(sendContent(const QString&)));

		QPushButton *btn = qFindChild<QPushButton*>(keyboard,"Key_A");
		mapper->setMapping(btn, "A");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));
		
		btn = qFindChild<QPushButton*>(keyboard,"Key_B");
		mapper->setMapping(btn, "B");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_C");
		mapper->setMapping(btn, "C");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_D");
		mapper->setMapping(btn, "D");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_E");
		mapper->setMapping(btn, "E");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_F");
		mapper->setMapping(btn, "F");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_G");
		mapper->setMapping(btn, "G");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_H");
		mapper->setMapping(btn, "H");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_I");
		mapper->setMapping(btn, "I");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_J");
		mapper->setMapping(btn, "J");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_K");
		mapper->setMapping(btn, "K");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_L");
		mapper->setMapping(btn, "L");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_M");
		mapper->setMapping(btn, "M");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_N");
		mapper->setMapping(btn, "N");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_O");
		mapper->setMapping(btn, "O");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_P");
		mapper->setMapping(btn, "P");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_Q");
		mapper->setMapping(btn, "Q");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_R");
		mapper->setMapping(btn, "R");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_S");
		mapper->setMapping(btn, "S");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_T");
		mapper->setMapping(btn, "T");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_U");
		mapper->setMapping(btn, "U");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_V");
		mapper->setMapping(btn, "V");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_W");
		mapper->setMapping(btn, "W");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_X");
		mapper->setMapping(btn, "X");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_Y");
		mapper->setMapping(btn, "Y");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_Z");
		mapper->setMapping(btn, "Z");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_Return");
		//connect(btn, SIGNAL(clicked()), im, SLOT(confirmContent()));
		mapper->setMapping(btn, "Return");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_Back");
		mapper->setMapping(btn, "Back");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_Shift");
		mapper->setMapping(btn, "Shift");
		btn->setCheckable(true);//
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_Num");
		mapper->setMapping(btn, "Num");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));

		btn = qFindChild<QPushButton*>(keyboard,"Key_Space");
		mapper->setMapping(btn, "Space");
		connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));
	}
}

void InputWidget::createPinyinTable()
{
	if(pinyinTable == NULL)
	{
		//cout<<"create pinyin table"<<endl;
		createKeyboard();

		pinyinTable = new MySelectList();
		//pinyinTable->hide();
		
		//数字选择键
		QSignalMapper* mapper = new QSignalMapper(this);
		connect(mapper, SIGNAL(mapped(const QString&)), im, SLOT(sendContent(const QString&)));
		int pn = pinyinTable->getPn();
		for(int i = 0; i < pn; ++i)
		{
			//cout<<"mapping"<<QString().setNum(i).toLocal8Bit().data()<<endl;
			mapper->setMapping(pinyinTable->btn[i], QString().setNum(i));
			QObject::connect(pinyinTable->btn[i], SIGNAL(clicked()), mapper, SLOT(map()));
		}
	}
}

void InputWidget::pinyin_refresh()
{
	IMFrame *im = dynamic_cast<IMFrame*>(this->im);
	pinyinTable->setList(im->getResultList());
	pinyinTable->refresh();

	/*
	QString showText;
	for(int i = im->getCurPg(); i < PAGECOUNT && i < (im->getResultList()).size(); ++i)
	{
		showText += QString::fromUtf8(QString().setNum((i+1)).toUtf8().data());
		showText += QString::fromUtf8("、");
		showText += QString::fromUtf8((im->getResultList())[i].toUtf8().data());
		showText += QString::fromUtf8("  ");
	}
	pinyinTable->setText(QObject::trUtf8(showText.toUtf8().data()));
	cout<<"the matched text is:"<<showText.toUtf8().data()<<endl;

	//QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QTextCodec *codec = QTextCodec::codecForLocale();
	pinyinTable->setText(codec->toUnicode(showText.toUtf8().data()));
	*/
	//pinyinTable->setText(showText);
}

void InputWidget::createHandWrite()
{
	if(handwrite == NULL)
	{
		QUiLoader loader;
		QFile file("./cfg/myHandWrite.ui");
		file.open(QFile::ReadOnly);
		handwrite = loader.load(&file, this); 
		file.close();

//		handwrite->show();
	}
}
void InputWidget::setMethodWidget(int select)
{
	if(select == PINYIN_METHOD)
	{
		pinyinTable->show();
		lay->setCurrentIndex(KEYBOARD_METHOD);
		return;
	}
	lay->setCurrentIndex(select);
}
InputWidget::~InputWidget()
{
}

