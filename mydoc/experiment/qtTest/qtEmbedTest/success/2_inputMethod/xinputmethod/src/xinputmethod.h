//处理用户输入的输入法核心部分
#ifndef _XINPUTMETHOD_8c8c9d7c8d7c9as678xc_
#define _XINPUTMETHOD_8c8c9d7c8d7c9as678xc_

#include <QWSInputMethod>



struct XInputMethodPrivate;

class XInputMethod : public QWSInputMethod
{
    Q_OBJECT

public:

	//加载和卸载输入法
    static void installInputMethod();
    static void releaseInputMethod();

	//调用构造函数创建一个类对象
    static XInputMethod* instance();

	//核心函数，处理用户输入(keycode)
	//截获用户输入用这个函数处理然后处理结果再输出到本应输出的编辑框
	//keycode:按下的键，应该是Qt::Key的一个值
	//modifiers:这个变量应该和Qt::KeyboardModifiers相与表示控制键
	//isPress:是否按下按键.	autoRepeat是否自动重复按键
	//函数返回true:表示会重复执行这个fileter这样才能不断获得用户输入并过滤。
	//默认返回flase。
    virtual bool filter(int unicode, int keycode, int modifiers,
                        bool isPress, bool autoRepeat);

    virtual ~XInputMethod();

private:
	//这里构造函数私有了,只能通过instance来调用它
    XInputMethod();
	
	////////下面是在"输入法上下文"中的各种响应
	//切换加载和卸载输入法输入"[Alt]z"
    void toggleIME();

	//存放用户输入，处理用户输入得到用户输出，保存输出结果
    void processCharacter(char);
	
	//这里响应用户选择（在出现重码的时候用户输入数字选择对应的结果）
    bool makeSelection(int);
	
	//重码过多则提供翻页以供方便选择
    void showNextPage();
    void showPreviousPage();

	////////输入法相关数据
	//包括：用户交互界面，处理前的用户输入及处理后的输出结果
    XInputMethodPrivate* mpdata;
};



//-------------------------------------------------------
#endif //_XINPUTMETHOD_8c8c9d7c8d7c9as678xc_
