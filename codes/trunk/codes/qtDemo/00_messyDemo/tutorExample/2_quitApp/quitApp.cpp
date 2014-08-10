/*程序功能：
 * 一个包含按钮的程序，可以设置按钮的显示字体，点击按钮程序退出。
 * */
#include<qapplication.h>
#include<qpushbutton.h>
//因为使用了QFont所以需要包含这个文件
#include<qfont.h>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QPushButton quit("Quit", 0);
	quit.resize(75, 30);
	
	//这里设置自己选择的字体
	quit.setFont(QFont("Times", 18, QFont::Bold));

	//signals发送消息，slots接收消息。在这里quit的clicked()信号和a的quit()槽连接
	//这样点击按钮导致程序退出了
	QObject::connect(&quit, SIGNAL(clicked()), &a, SLOT(quit()));

	a.setMainWidget(&quit);
	quit.show();
	return a.exec();
}
