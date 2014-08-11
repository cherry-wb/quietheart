#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
#include "imframe.h"
#include "./pinYinEngine/neuInterface.h"
#include "inputwidget.h"
using std::cout;
using std::endl;

IMFrame::IMFrame()
{
	inputwidget = new InputWidget(this);
	inputwidget->show();
	if(inputwidget->select != PINYIN_METHOD)
	{
		inputwidget->pinyinTable->hide();
	}
	state = KEY_BOARD;
	cur_pg = 0;
}

IMFrame::~IMFrame()
{
}

bool IMFrame::filter(int unicode, int keycode, int modifiers,
                                bool isPress, bool autoRepeat)
{
	//如果用户输入按键为[Alt]z，则切换输入法
	//if (isPress && (Qt::AltModifier & modifiers) && (Qt::Key_Z == keycode))
	//{

	//  return true;
	//}

	//cout<<"filter key is:"<<keycode<<endl;
	if(state == KEY_BOARD)
	{
		if(inputwidget->select == KEYBOARD_METHOD)
		{
			if ((Qt::Key_A <= keycode) && (Qt::Key_Z >= keycode))
			{
				char ch = (char)((Qt::ShiftModifier & modifiers) ? 
						keycode : (keycode - Qt::Key_A + 'a'));
				sendCommitString(QString(ch));
			}
			else if(Qt::Key_Space == keycode)
			{
				char ch = (char)keycode;
				sendCommitString(QString(ch));
			}
			return true;
		}
		else if(inputwidget->select == PINYIN_METHOD)
		{
			//cout<<"filter key space is:"<<Qt::Key_Space<<endl;
			//cout<<"filter key return is:"<<Qt::Key_Return<<endl;
			if ((Qt::Key_A <= keycode) && (Qt::Key_Z >= keycode))
			{
				char ch = (char)((Qt::ShiftModifier & modifiers) ? 
						keycode : (keycode - Qt::Key_A + 'a'));
				processCharacter(ch);
			}
			else if(Qt::Key_Backspace == keycode)
			{
				if(strPinyin.length() > 0)
				{
					strPinyin.remove(strPinyin.length()-1, 1);
					processCharacter(0);
				}
				else
				{
					return false;
				}
			}
			else if((Qt::Key_0 <= keycode) && (Qt::Key_5 >= keycode))
			{//按下数字键进行选择
				QString selRes = inputwidget->pinyinTable->getSelChar(keycode - Qt::Key_0);
				sendCommitString(selRes);
				strPinyin.clear();
				listResult.clear();
			}
			else if(Qt::Key_Space == keycode || Qt::Key_Return == keycode)
			{//空格与回车选择第一个字
				if(!strPinyin.isEmpty())
				{
					if(listResult.size() > 0)
					{
						sendCommitString(listResult[0]);
						strPinyin.clear();
						listResult.clear();
					}
					else
					{
						sendCommitString(strPinyin);
						strPinyin.clear();
					}
				}
				else
				{
					if(Qt::Key_Space == keycode)
					{
						char ch = (char)keycode;
						sendCommitString(QString(ch));
					}
					else
					{
						return false;
					}
				}
			}
			return true;
		}
		return false;
	}
	else
	{
		return false;
	}
}
bool IMFrame::filter(const QPoint & position, int state, int wheel)
{
	static bool pressed = false;
	if(this->state == HAND_WRITE)
	{
		if(state & Qt::LeftButton)
		{
			cout<<"press left at"<<position.x()<<','<<position.y()<<endl;
			pressed = true;
			return true;
		}
		else
		{
			if(pressed)
			{//如果是从按下状态转来的就处理绘制的图形翻译成文字
				cout<<"released button!"<<endl;
				pressed =false;
				return true;
			}
			return false;
		}
	}
	return false;
	//if(state & Qt::RightButton)
	//{
	//	cout<<"press right at"<<position.x()<<','<<position.y()<<endl;
	//}
	//if(state & Qt::MidButton)
	//{
	//	cout<<"press middle at"<<position.x()<<','<<position.y()<<endl;
	//}
	//cout<<"the wheel is:"<<wheel<<endl;
}

void IMFrame::processCharacter(char ch)
{
	//获取用户输入的拼音
	if(ch != 0)
	{
		strPinyin += ch;
	}

	//cout<<"process:"<<strPinyin.toLocal8Bit().data()<<endl;
	
	//得到相应拼音的输出（多个汉字的列表）
	NeuPinYin proc(strPinyin); 
	proc.processInput();
	listResult = proc.getResultList();
	//cout<<"matched hanzi"<<proc.getMatchCount()<<endl;

	/*
	listResult<<"first";
	listResult<<"second";
	listResult<<"third";
	listResult<<"forth";
	listResult<<"fifth";
	listResult<<"sixth";
	listResult<<"seventh";
	listResult<<"eighth";
	listResult<<"ninth";
	listResult<<"tenth";
	*/

	//刷新显示多个结果以供选择
	//inputWidget->update();

	inputwidget->pinyin_refresh();
	
	//输入自动上屏
	sendPreeditString(strPinyin,0);
	//结果自动上屏
	//sendPreeditString(listResult[0],0);
	
}
void IMFrame::sendKeyBoardContent(const QString &key)
{
	int unicode = -1;
	int keycode = 0;
	static Qt::KeyboardModifiers modifiers = Qt::NoModifier;
	bool isPress = true;
	bool autoRepeat = false;
	if (key == "A")
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
			modifiers = Qt::ShiftModifier;
		}
		keycode = Qt::Key_Shift;
	}
	else if(key == "Back")
	{
		keycode = Qt::Key_Backspace;
	}
	else if(key == "Return")
	{
		keycode = Qt::Key_Return;
	}
	else if(key == "Space")
	{
		keycode = Qt::Key_Space;
	}
	else
	{
		cout<<"unknown key!"<<endl;
		return ;
	}
	QWSServer::sendKeyEvent( unicode, keycode, modifiers, isPress, autoRepeat);
}
void IMFrame::sendContent(const QString& newcontent)
{
	//content += newcontent;
	//sendPreeditString(content,0);
	if(state == KEY_BOARD)
	{
		sendKeyBoardContent(newcontent);
	}
}

void IMFrame::confirmContent()
{
	sendCommitString(content);
	content.clear();
}

void IMFrame::updateHandler(int type)
{
	switch(type)
	{
	case QWSInputMethod::FocusOut:
		content.clear();
		break;
	default:
		break;
	}
}
int IMFrame::getCurPg()
{
	if(inputwidget != NULL && inputwidget->pinyinTable != NULL)
	{
		cur_pg = inputwidget->pinyinTable->getPg();
	}
	else
	{
		cur_pg = 0;
	}
	return cur_pg;
}
QStringList& IMFrame::getResultList()
{
	return listResult;
}
