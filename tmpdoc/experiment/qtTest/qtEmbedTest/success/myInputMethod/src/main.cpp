#include <QApplication>
#include <QFont>
#include "imframe.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	
	//选择字体
	app.setFont(QFont("wenquanyi", 10));

	QWSInputMethod* im = new IMFrame;
	//这样就会显示输入法控件了
	QWSServer::setCurrentInputMethod(im);	

	return app.exec();
}
