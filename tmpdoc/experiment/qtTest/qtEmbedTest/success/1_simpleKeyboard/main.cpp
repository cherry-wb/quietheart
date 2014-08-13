#include <QApplication>
#include "imframe.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QWSInputMethod* im = new IMFrame;
	//这样就会显示输入法控件了
	QWSServer::setCurrentInputMethod(im);	

	return app.exec();
}
