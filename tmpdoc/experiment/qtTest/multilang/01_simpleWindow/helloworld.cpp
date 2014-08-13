/* 程序功能：只有一个窗口的helloworld程序。
 * 编译过程：
 * $qmake -project
 * $qmake
 * $make
 * 在X窗口运行的时候可以尝试用-geometry 100x200+10+20来指定大小试试。
 * */
#include <QApplication>
#include <QWidget>
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	QWidget window;
	window.resize(320, 240);
	window.show();

	return a.exec();
}

