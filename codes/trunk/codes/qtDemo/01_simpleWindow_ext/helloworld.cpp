/* 程序功能：只有一个窗口的helloworld程序。
 * 该程序设置窗口没有标题栏等特性，有待添加。
 * */
#include <QApplication>
#include <QWidget>
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	QWidget window;
	//设置窗口没有标题栏
	//window.setFrameStyle(QFrame::NoFrame)
	window.setWindowFlags(Qt::FramelessWindowHint);

	window.resize(320, 240);
	window.show();

	return a.exec();
}

