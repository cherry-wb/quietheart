#include <QApplication>
//#include <QTextCodec>
//#include <QLabel>
//#include <QString>
#include "xinputmethod.h"
#include "ximewindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    const QApplication::Type type = app.type();

	//QApplication::Tty一个控制台程序
	//QApplication::GuiClient Gui的client程序
	//QApplication::GuiServer Gui的server程序用于嵌入式linux的Qt
    if (QApplication::GuiServer == type)
    {
        XInputMethod::installInputMethod();
    }


    int nret = app.exec();

    if (QApplication::GuiServer == type)
        XInputMethod::releaseInputMethod();

    return nret;
}

