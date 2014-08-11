#include <QWSServer>
#include <QApplication>
#include <QTextCodec>
#include <QStringList>

#include "ximedata.h"
#include "ximewindow.h"
#include "xinputmethod.h"



struct XInputMethodPrivate
{
	static XInputMethod* pInputMethod;

	//用户界面
	XWindow* pframe;

	//存放处理前和处理后的数据
	//处理前的就是用户输入的最原始数据，处理后的就是将要发送到编辑框中的数据
	XData imedata;

	XInputMethodPrivate(): pframe(NULL) {}
};


XInputMethod* XInputMethodPrivate::pInputMethod = NULL;

void XInputMethod::installInputMethod()
{
    XInputMethod* pim = instance();
   
    if (pim)
    {
        QWSServer::setCurrentInputMethod(pim);
    }
}

void XInputMethod::releaseInputMethod()
{
    if (XInputMethodPrivate::pInputMethod)
    {
        QWSServer::setCurrentInputMethod(NULL);
        delete XInputMethodPrivate::pInputMethod;
        XInputMethodPrivate::pInputMethod = NULL;
    }
}

XInputMethod* XInputMethod::instance()
{
    if (NULL == XInputMethodPrivate::pInputMethod)
    {
        XInputMethodPrivate::pInputMethod = new XInputMethod();
    }
    
    return XInputMethodPrivate::pInputMethod;
}

XInputMethod::XInputMethod(): mpdata(new XInputMethodPrivate)
{
	//pframe是用户界面
    mpdata->pframe = new XWindow(mpdata->imedata);
}

XInputMethod::~XInputMethod()
{
    if (mpdata)
    {
        delete mpdata->pframe;
        delete mpdata;
        mpdata = NULL;
    }
}

bool XInputMethod::filter(int /*unicode*/, int keycode, int modifiers,
                                bool isPress, bool /*autoRepeat*/)
{//处理用户输入
	//如果用户输入按键为[Alt]z，则切换输入法
    if (isPress && (Qt::AltModifier & modifiers) && (Qt::Key_Z == keycode))
    {
        toggleIME();

        return true;
    }


    if (mpdata && mpdata->pframe && mpdata->pframe->isVisible() && isPress)
    {//如果输入法的用户交互界面存在，并且已经按键
        if ((Qt::Key_A <= keycode) && (Qt::Key_Z >= keycode))
        {//如果按键是字母键
			//获得用户输入字符ch
            char ch = (char)((Qt::ShiftModifier & modifiers) ? 
                             keycode : (keycode - Qt::Key_A + 'a'));

			//处理用户输入，得到用户输出并显示。
			//用户输入和输出会被保存起来,便于处理。
            processCharacter(ch);

			//如果返回false就会进一步交由父类的filter处理，否则不。
            return true;
        }

        if ((Qt::Key_0 <= keycode) && (Qt::Key_9 >= keycode))
        {//用户根据显示的多个结果按下数字键选择相应结果
            return makeSelection(keycode - Qt::Key_0);
        }

        if (Qt::Key_PageDown == keycode)
        {//翻页
            showNextPage();
            return true;
        }

        if (Qt::Key_PageUp == keycode)
        {//翻页
            showPreviousPage();
            return true;
        }
    }

    return false;
}


void XInputMethod::toggleIME()
{
    if (mpdata->pframe->isVisible())
    {
		//隐藏输入法的用户界面
        mpdata->pframe->hide();
		//重置(清空)输入法中的数据(处理前的和处理后的)
        mpdata->imedata.reset();
    }
    else
    {
        mpdata->pframe->show();
    }
}


void XInputMethod::processCharacter(char ch)
{
	//将用户输入存放起来（存放在mpdata->imedata.strPinyin）
    mpdata->imedata.strPinyin += ch;

	//处理用户输入得到用户输出并保存(存放在mpdata->imedata.listHanzi)
	//这里为了简化，没有处理用户输入，无论什么输入都是如下的输出。
	//输出的是26个结果（重码了），对应26个字母。
    mpdata->imedata.listHanzi << "a";
    mpdata->imedata.listHanzi << "b";
    mpdata->imedata.listHanzi << "c";
    mpdata->imedata.listHanzi << "d";
    mpdata->imedata.listHanzi << "e";
    mpdata->imedata.listHanzi << "f";
    mpdata->imedata.listHanzi << "g";
    mpdata->imedata.listHanzi << "h";
    mpdata->imedata.listHanzi << "i";
    mpdata->imedata.listHanzi << "j";
    mpdata->imedata.listHanzi << "k";
    mpdata->imedata.listHanzi << "l";
    mpdata->imedata.listHanzi << "m";
    mpdata->imedata.listHanzi << "n";
    mpdata->imedata.listHanzi << "o";
    mpdata->imedata.listHanzi << "p";
    mpdata->imedata.listHanzi << "q";
    mpdata->imedata.listHanzi << "r";
    mpdata->imedata.listHanzi << "s";
    mpdata->imedata.listHanzi << "t";
    mpdata->imedata.listHanzi << "u";
    mpdata->imedata.listHanzi << "v";
    mpdata->imedata.listHanzi << "w";
    mpdata->imedata.listHanzi << "x";
    mpdata->imedata.listHanzi << "y";
    mpdata->imedata.listHanzi << "z";

	//将用户输出显示到输入法构件上方便用户选择
    mpdata->pframe->update();
}

bool XInputMethod::makeSelection(int number)
{//用户选择结果
    number--;

    if ((mpdata->imedata.first_visible + number) < mpdata->imedata.listHanzi.count())
    {//多个"重码"结果存放在imedata列表中，根据数字进行选择，返回到result中
        QString result = mpdata->imedata.listHanzi[mpdata->imedata.first_visible + number];

        if (!result.isEmpty())
        {
			//这里把选择的结果发送出去，导致最终出现在编辑框中了
            sendCommitString(result);
            mpdata->imedata.reset();//选择后清空输入输出数据
            mpdata->pframe->update();//刷新输入发控件显示

            return true;
        }
    }

    return false;
}


void XInputMethod::showNextPage()
{//多个结果翻页
    if ((mpdata->imedata.first_visible + mpdata->imedata.counts_per_page) < mpdata->imedata.listHanzi.count())
    {
        mpdata->imedata.first_visible += mpdata->imedata.counts_per_page;//指定下一页内容
        mpdata->pframe->update();//更新显示
    }
}

void XInputMethod::showPreviousPage()
{
    if ((mpdata->imedata.first_visible - mpdata->imedata.counts_per_page) >= 0)
    {
        mpdata->imedata.first_visible -= mpdata->imedata.counts_per_page;
        mpdata->pframe->update();
    }
}
