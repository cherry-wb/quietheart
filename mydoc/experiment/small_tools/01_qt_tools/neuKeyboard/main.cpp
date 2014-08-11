/*程序功能：一个Qt软键盘的界面程序。
 * 提供的接口包括：
 * 1)设置键盘的显示模式：（字母，数字符号等）
   void setKbdMode(const KbdMode &mode);
 * 2)按下键盘按键发出的信号：
   void keyPress(int unicode, int keycode, 
   		Qt::KeyboardModifiers modifiers, bool isPress, bool autoRepeat);
   其他的参见头文件。
 * */

#include <QApplication>
#include "neuKeyboard.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	NeuKeyboard kbd;
	kbd.show();
	return app.exec();
}
