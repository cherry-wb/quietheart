#include <QPushButton>
#include <QGridLayout>
#include <QStringList>
#include <QSignalMapper>
#include <iostream>
#include "neuKeyboard.h"
using std::cout;
using std::endl;
NeuKeyboard::NeuKeyboard(QWidget *parent):QWidget(parent)
{
	mapper = NULL;
	m_mode = NORMAL;
	kbdGrid = new QGridLayout(this);
	kbdGrid->setSpacing(2);
	//kbdGrid->setMargin(2);
	kbdGrid->setContentsMargins(0,2,2,2);
	addButtons(kbdGrid);
	initTxt();
	setKbdMode(m_mode);
}

void NeuKeyboard::addButtons(QGridLayout *kbdGrid)
{
	if(mapper)
	{
		delete mapper;
	}
	mapper = new QSignalMapper(this);
	QObject::connect(mapper, SIGNAL(mapped(const QString&)), this, SLOT(sendKey(const QString&)));
	//button of first row
	//qwert,yuiop or etc
	for(int i = 0; i < MY_ROW1_COUNT; ++i)
	{
		btns1[i] = new QPushButton;
		QObject::connect(btns1[i], SIGNAL(clicked()), mapper, SLOT(map()));
	}
	for(int i = 0; i < MY_ROW1_COUNT; ++i)
	{
		kbdGrid->addWidget(btns1[i],0,i<<2,1,4);//4 cells for each button
	}

	//button of second row
	//asdfg,hjkl or etc
	for(int i = 0; i < MY_ROW2_COUNT; ++i)
	{
		btns2[i] = new QPushButton;
		QObject::connect(btns2[i], SIGNAL(clicked()), mapper, SLOT(map()));
	}
	for(int i = 0; i < MY_ROW2_COUNT; ++i)
	{
		kbdGrid->addWidget(btns2[i],1,2+(i<<2),1,4);//4 cells for each button
	}
	
	//button of third row
	//Shift,zxcvb,nm,backspace or etc
	for(int i = 0; i < MY_ROW3_COUNT; ++i)
	{
		btns3[i] = new QPushButton;
		QObject::connect(btns3[i], SIGNAL(clicked()), mapper, SLOT(map()));
	}
	kbdGrid->addWidget(btns3[0],2,0,1,5);//5 cells for button
	for(int i = 1; i < MY_ROW3_COUNT - 1; ++i)
	{
		kbdGrid->addWidget(btns3[i],2,2+(i<<2),1,4);
	}
	kbdGrid->addWidget(btns3[MY_ROW3_COUNT - 1],2,35,1,5);//5 cells for button
	
	//button of forth row
	//?123,Space,Return
	for(int i = 0; i < MY_ROW4_COUNT; ++i)
	{
		btns4[i] = new QPushButton;
		QObject::connect(btns4[i], SIGNAL(clicked()), mapper, SLOT(map()));
	}
	kbdGrid->addWidget(btns4[0],3,0,1,9);//9 cells for button
	kbdGrid->addWidget(btns4[1],3,10,1,20);//9 cells for button
	kbdGrid->addWidget(btns4[2],3,31,1,9);//9 cells for button
}

void NeuKeyboard::initTxt()
{
	//normal
	btns1NormalTxt<<"Q";
	btns1NormalTxt<<"W";
	btns1NormalTxt<<"E";
	btns1NormalTxt<<"R";
	btns1NormalTxt<<"T";
	btns1NormalTxt<<"Y";
	btns1NormalTxt<<"U";
	btns1NormalTxt<<"I";
	btns1NormalTxt<<"O";
	btns1NormalTxt<<"P";

	btns2NormalTxt<<"A";
	btns2NormalTxt<<"S";
	btns2NormalTxt<<"D";
	btns2NormalTxt<<"F";
	btns2NormalTxt<<"G";
	btns2NormalTxt<<"H";
	btns2NormalTxt<<"J";
	btns2NormalTxt<<"K";
	btns2NormalTxt<<"L";

	btns3NormalTxt<<"Shift";//maybe icon
	btns3NormalTxt<<"Z";
	btns3NormalTxt<<"X";
	btns3NormalTxt<<"C";
	btns3NormalTxt<<"V";
	btns3NormalTxt<<"B";
	btns3NormalTxt<<"N";
	btns3NormalTxt<<"M";
	btns3NormalTxt<<"BackSpace";//maybe icon

	btns4NormalTxt<<"?123";
	btns4NormalTxt<<"Space";
	btns4NormalTxt<<"Return";
	
	//symbol1 needs to be confirmed
	btns1Symbol1Txt<<"1";
	btns1Symbol1Txt<<"2";
	btns1Symbol1Txt<<"3";
	btns1Symbol1Txt<<"4";
	btns1Symbol1Txt<<"5";
	btns1Symbol1Txt<<"6";
	btns1Symbol1Txt<<"7";
	btns1Symbol1Txt<<"8";
	btns1Symbol1Txt<<"9";
	btns1Symbol1Txt<<"0";

	btns2Symbol1Txt<<"!";
	btns2Symbol1Txt<<"@";
	btns2Symbol1Txt<<"#";
	btns2Symbol1Txt<<"$";
	btns2Symbol1Txt<<"%";
	btns2Symbol1Txt<<"^";
	btns2Symbol1Txt<<"&&";
	btns2Symbol1Txt<<"*";
	btns2Symbol1Txt<<"(";

	btns3Symbol1Txt<<"None";//maybe icon
	btns3Symbol1Txt<<")";
	btns3Symbol1Txt<<"_";
	btns3Symbol1Txt<<"-";
	btns3Symbol1Txt<<"+";
	btns3Symbol1Txt<<"=";
	btns3Symbol1Txt<<"~";
	btns3Symbol1Txt<<"`";
	btns3Symbol1Txt<<"BackSpace";//maybe icon

	btns4Symbol1Txt<<"?'</";
	btns4Symbol1Txt<<"Space";
	btns4Symbol1Txt<<"Return";

	//symbol2 needs to be confirmed
	btns1Symbol2Txt<<"1";
	btns1Symbol2Txt<<"2";
	btns1Symbol2Txt<<"3";
	btns1Symbol2Txt<<"4";
	btns1Symbol2Txt<<"5";
	btns1Symbol2Txt<<"6";
	btns1Symbol2Txt<<"7";
	btns1Symbol2Txt<<"8";
	btns1Symbol2Txt<<"9";
	btns1Symbol2Txt<<"0";

	btns2Symbol2Txt<<"[";
	btns2Symbol2Txt<<"]";
	btns2Symbol2Txt<<"{";
	btns2Symbol2Txt<<"}";
	btns2Symbol2Txt<<";";
	btns2Symbol2Txt<<":";
	btns2Symbol2Txt<<"'";
	btns2Symbol2Txt<<"\"";
	btns2Symbol2Txt<<"<";

	btns3Symbol2Txt<<"None";//maybe icon
	btns3Symbol2Txt<<">";
	btns3Symbol2Txt<<",";
	btns3Symbol2Txt<<".";
	btns3Symbol2Txt<<"/";
	btns3Symbol2Txt<<"?";
	btns3Symbol2Txt<<"|";
	btns3Symbol2Txt<<"\\";
	btns3Symbol2Txt<<"BackSpace";//maybe icon

	btns4Symbol2Txt<<"?ABC";
	btns4Symbol2Txt<<"Space";
	btns4Symbol2Txt<<"Return";
}
void NeuKeyboard::setKbdMode(const KbdMode &mode)
{
	switch(mode)
	{
		case NORMAL:
		;
		case SHIFT:
		for(int i = 0; i < MY_ROW1_COUNT; ++i)
		{
			btns1[i]->setText(btns1NormalTxt[i]);
			mapper->setMapping(btns1[i],btns1[i]->text());
		}
		for(int i = 0; i < MY_ROW2_COUNT; ++i)
		{
			btns2[i]->setText(btns2NormalTxt[i]);
			mapper->setMapping(btns2[i],btns2[i]->text());
		}
		for(int i = 0; i < MY_ROW3_COUNT; ++i)
		{
			btns3[i]->setText(btns3NormalTxt[i]);
			mapper->setMapping(btns3[i],btns3[i]->text());
		}
		for(int i = 0; i < MY_ROW4_COUNT; ++i)
		{
			btns4[i]->setText(btns4NormalTxt[i]);
			mapper->setMapping(btns4[i],btns4[i]->text());
		}
		break;

		case SYMBOL1:
		for(int i = 0; i < MY_ROW1_COUNT; ++i)
		{
			btns1[i]->setText(btns1Symbol1Txt[i]);
			mapper->setMapping(btns1[i],btns1[i]->text());
		}
		for(int i = 0; i < MY_ROW2_COUNT; ++i)
		{
			btns2[i]->setText(btns2Symbol1Txt[i]);
			mapper->setMapping(btns2[i],btns2[i]->text());
		}
		for(int i = 0; i < MY_ROW3_COUNT; ++i)
		{
			btns3[i]->setText(btns3Symbol1Txt[i]);
			mapper->setMapping(btns3[i],btns3[i]->text());
		}
		for(int i = 0; i < MY_ROW4_COUNT; ++i)
		{
			btns4[i]->setText(btns4Symbol1Txt[i]);
			mapper->setMapping(btns4[i],btns4[i]->text());
		}
		break;
		case SYMBOL2:
		for(int i = 0; i < MY_ROW1_COUNT; ++i)
		{
			btns1[i]->setText(btns1Symbol2Txt[i]);
			mapper->setMapping(btns1[i],btns1[i]->text());
		}
		for(int i = 0; i < MY_ROW2_COUNT; ++i)
		{
			btns2[i]->setText(btns2Symbol2Txt[i]);
			mapper->setMapping(btns2[i],btns2[i]->text());
		}
		for(int i = 0; i < MY_ROW3_COUNT; ++i)
		{
			btns3[i]->setText(btns3Symbol2Txt[i]);
			mapper->setMapping(btns3[i],btns3[i]->text());
		}
		for(int i = 0; i < MY_ROW4_COUNT; ++i)
		{
			btns4[i]->setText(btns4Symbol2Txt[i]);
			mapper->setMapping(btns4[i],btns4[i]->text());
		}
		break;
		default:
		break;
	}
}

void NeuKeyboard::sendKey(const QString &key)
{
	int unicode = -1;
	int keycode = 0;
	static Qt::KeyboardModifiers modifiers = Qt::NoModifier;
	bool isPress = true;
	bool autoRepeat = false;
	//switch(key)
	//{
		//...switch cann't be used for type that isn't int
	//}
	
	//special key
	if(key == "?123")
	{
		cout<<"mode change!"<<endl;
		modifiers = Qt::NoModifier;
		setKbdMode(SYMBOL1);
		return;
	}
	if(key == "?'</")
	{
		cout<<"mode change!"<<endl;
		setKbdMode(SYMBOL2);
		return;
	}
	if(key == "?ABC")
	{
		cout<<"mode change!"<<endl;
		setKbdMode(NORMAL);
		return;
	}
	//common key
	else if(key == "Return")
	{
		keycode = Qt::Key_Return;
	}
	else if(key == "BackSpace")
	{
		keycode = Qt::Key_Backspace;
	}
	else if(key == "Space")
	{
		keycode = Qt::Key_Space;
	}
	else if(key == "Shift")
	{
		//if(Shift.isFlat())
		if(modifiers == Qt::ShiftModifier)
		{
			//Shift.setFlat(false);
			modifiers = Qt::NoModifier;
		}
		else
		{
			//Shift.setFlat(true);
			modifiers |= Qt::ShiftModifier;
		}
		keycode = Qt::Key_Shift;
	}
	//alpha key
	else if (key == "A")
	{
		keycode = Qt::Key_A;
	}
	else if(key == "B")
	{
		keycode = Qt::Key_B;
	}
	else if(key == "C")
	{
		keycode = Qt::Key_C;
	}
	else if(key == "D")
	{
		keycode = Qt::Key_D;
	}
	else if(key == "E")
	{
		keycode = Qt::Key_E;
	}
	else if(key == "F")
	{
		keycode = Qt::Key_F;
	}
	else if(key == "G")
	{
		keycode = Qt::Key_G;
	}
	else if(key == "H")
	{
		keycode = Qt::Key_H;
	}
	else if(key == "I")
	{
		keycode = Qt::Key_I;
	}
	else if(key == "J")
	{
		keycode = Qt::Key_J;
	}
	else if(key == "K")
	{
		keycode = Qt::Key_K;
	}
	else if(key == "L")
	{
		keycode = Qt::Key_L;
	}
	else if(key == "M")
	{
		keycode = Qt::Key_M;
	}
	else if(key == "N")
	{
		keycode = Qt::Key_N;
	}
	else if(key == "O")
	{
		keycode = Qt::Key_O;
	}
	else if(key == "P")
	{
		keycode = Qt::Key_P;
	}
	else if(key == "Q")
	{
		keycode = Qt::Key_Q;
	}
	else if(key == "R")
	{
		keycode = Qt::Key_R;
	}
	else if(key == "S")
	{
		keycode = Qt::Key_S;
	}
	else if(key == "T")
	{
		keycode = Qt::Key_T;
	}
	else if(key == "U")
	{
		keycode = Qt::Key_U;
	}
	else if(key == "V")
	{
		keycode = Qt::Key_V;
	}
	else if(key == "W")
	{
		keycode = Qt::Key_W;
	}
	else if(key == "X")
	{
		keycode = Qt::Key_X;
	}
	else if(key == "Y")
	{
		keycode = Qt::Key_Y;
	}
	else if(key == "Z")
	{
		keycode = Qt::Key_Z;
	}
	else if(key == "0")
	{
		keycode = Qt::Key_0;
	}
	//symbol1
	else if(key == "0")
	{
		keycode = Qt::Key_0;
	}
	else if(key == "1")
	{
		keycode = Qt::Key_1;
	}
	else if(key == "2")
	{
		keycode = Qt::Key_2;
	}
	else if(key == "3")
	{
		keycode = Qt::Key_3;
	}
	else if(key == "4")
	{
		keycode = Qt::Key_4;
	}
	else if(key == "5")
	{
		keycode = Qt::Key_5;
	}
	else if(key == "6")
	{
		keycode = Qt::Key_6;
	}
	else if(key == "7")
	{
		keycode = Qt::Key_7;
	}
	else if(key == "8")
	{
		keycode = Qt::Key_8;
	}
	else if(key == "9")
	{
		keycode = Qt::Key_9;
	}
	else if(key == "0")
	{
		keycode = Qt::Key_0;
	}
	else if(key == "!")
	{
		keycode = Qt::Key_Exclam;
		unicode = Qt::Key_Exclam;
	}
	else if(key == "@")
	{
		keycode = Qt::Key_At;
		unicode = Qt::Key_At;
	}
	else if(key == "#")
	{
		keycode = Qt::Key_NumberSign;
		unicode = Qt::Key_NumberSign;
	}
	else if(key == "$")
	{
		keycode = Qt::Key_Dollar;//right
		unicode = Qt::Key_Dollar;//right
	}
	else if(key == "%")
	{
		keycode = Qt::Key_Percent;//right
		unicode = Qt::Key_Percent;//right
	}
	else if(key == "^")
	{
		keycode = Qt::Key_AsciiCircum;//right
		unicode = Qt::Key_AsciiCircum;//right
	}
	else if(key == "&&")
	{
		//cout<<"&"<<endl;
		keycode = Qt::Key_Ampersand;//right
		unicode = Qt::Key_Ampersand;//right
	}
	else if(key == "*")
	{
		keycode = Qt::Key_Asterisk;//right
		unicode = Qt::Key_Asterisk;//right
	}
	else if(key == "(")
	{
		keycode = Qt::Key_ParenLeft;
		unicode = Qt::Key_ParenLeft;
	}
	else if(key == ")")
	{
		keycode = Qt::Key_ParenRight;
		unicode = Qt::Key_ParenRight;
	}
	else if(key == "_")
	{
		keycode = Qt::Key_Underscore;
		unicode = Qt::Key_Underscore;
	}
	else if(key == "-")
	{
		keycode = Qt::Key_Minus;
		unicode = Qt::Key_Minus;
	}
	else if(key == "+")
	{
		keycode = Qt::Key_Plus;
		unicode = Qt::Key_Plus;
	}
	else if(key == "=")
	{
		keycode = Qt::Key_Equal;
		unicode = Qt::Key_Equal;
	}
	else if(key == "~")
	{
		keycode = Qt::Key_AsciiTilde;
		unicode = Qt::Key_AsciiTilde;
	}
	else if(key == "`")
	{
		keycode = Qt::Key_QuoteLeft;
		unicode = Qt::Key_QuoteLeft;
	}
	//symbol2
	else if(key == "[")
	{
		keycode = Qt::Key_BracketLeft;
		unicode = Qt::Key_BracketLeft;
	}
	else if(key == "]")
	{
		keycode = Qt::Key_BracketRight;
		unicode = Qt::Key_BracketRight;
	}
	else if(key == "{")
	{
		keycode = Qt::Key_BraceLeft;
		unicode = Qt::Key_BraceLeft;
	}
	else if(key == "}")
	{
		keycode = Qt::Key_BraceRight;
		unicode = Qt::Key_BraceRight;
	}
	else if(key == ";")
	{
		keycode = Qt::Key_Semicolon;
		unicode = Qt::Key_Semicolon;
	}
	else if(key == ":")
	{
		keycode = Qt::Key_Colon;
		unicode = Qt::Key_Colon;
	}
	else if(key == "'")
	{
		keycode = Qt::Key_Apostrophe;
		unicode = Qt::Key_Apostrophe;
	}
	else if(key == "\"")
	{
		keycode = Qt::Key_QuoteDbl;
		unicode = Qt::Key_QuoteDbl;
	}
	else if(key == "<")
	{
		keycode = Qt::Key_Less;
		unicode = Qt::Key_Less;
	}
	else if(key == ">")
	{
		keycode = Qt::Key_Greater;
		unicode = Qt::Key_Greater;
	}
	else if(key == ",")
	{
		keycode = Qt::Key_Comma;
		unicode = Qt::Key_Comma;
	}
	else if(key == ".")
	{
		keycode = Qt::Key_Period;
		unicode = Qt::Key_Period;
	}
	else if(key == "/")
	{
		keycode = Qt::Key_Slash;
		unicode = Qt::Key_Slash;
	}
	else if(key == "?")
	{
		keycode = Qt::Key_Question;
		unicode = Qt::Key_Question;
	}
	else if(key == "|")
	{
		keycode = Qt::Key_Bar;
		unicode = Qt::Key_Bar;
	}
	else if(key == "\\")
	{
		keycode = Qt::Key_Backslash;
		unicode = Qt::Key_Backslash;
	}
	else
	{
		cout<<"unknown key!"<<endl;
		return ;
	}
	//QWSServer::sendKeyEvent( unicode, keycode, modifiers, isPress, autoRepeat);
	if((keycode >= Qt::Key_A) && (keycode <= Qt::Key_Z))
	{
		if(modifiers & Qt::ShiftModifier)
		{
			keycode = toupper(keycode);
			unicode = toupper(keycode);
			modifiers &= (~Qt::ShiftModifier);
		}
	}
	emit keyPress(unicode, keycode, modifiers, isPress, autoRepeat);
}
