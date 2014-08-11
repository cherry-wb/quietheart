#ifndef __NEUKEYBOARD_H
#define __NEUKEYBOARD_H
#include <QWidget>
#define MY_ROW1_COUNT 10
#define MY_ROW2_COUNT 9
#define MY_ROW3_COUNT 9
#define MY_ROW4_COUNT 3
class QPushButton;
class QGridLayout;
class QStringList;
class QString;
class QSignalMapper;
class NeuKeyboard:public QWidget
{
	Q_OBJECT
	public:
	enum KbdMode
	{
		NORMAL = 0,
		SHIFT,
		SYMBOL1,
		SYMBOL2
	};
	KbdMode m_mode;

	public:
	NeuKeyboard(QWidget *parent = 0);
	void setKbdMode(const KbdMode &mode);


	signals:
	void keyPress(int unicode, int keycode, Qt::KeyboardModifiers modifiers, bool isPress, bool autoRepeat);

	private slots:
	void sendKey(const QString &key);

	private:
	void addButtons(QGridLayout *kbdGrid);
	void initTxt();

	private:
	QSignalMapper *mapper;

	//keyboard grid and buttons
	QGridLayout *kbdGrid;
	QPushButton *btns1[MY_ROW1_COUNT];//qwert,yuiop or etc
	QPushButton *btns2[MY_ROW2_COUNT];//asdfg,hjkl or etc
	QPushButton *btns3[MY_ROW3_COUNT];//Shift,zxcvb,nm,backspace or etc
	QPushButton *btns4[MY_ROW4_COUNT];//?123,Space,Return

	//button text
	QStringList btns1NormalTxt;
	QStringList btns2NormalTxt;
	QStringList btns3NormalTxt;
	QStringList btns4NormalTxt;
	
	QStringList btns1Symbol1Txt;
	QStringList btns2Symbol1Txt;
	QStringList btns3Symbol1Txt;
	QStringList btns4Symbol1Txt;

	QStringList btns1Symbol2Txt;
	QStringList btns2Symbol2Txt;
	QStringList btns3Symbol2Txt;
	QStringList btns4Symbol2Txt;
};
#endif
