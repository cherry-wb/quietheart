/* 程序功能：窗口内只有一个按钮，点击按钮关闭程序。
 * 编译过程：
 * $qmake -project
 * $qmake
 * $make
 * 在X窗口运行的时候可以尝试用-geometry 100x200+10+20来指定大小试试。
 * */
#include <QApplication>
#include <QWidget>
#include <QPushButton>
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	QWidget window;
	window.resize(320, 240);
	window.show();

	//指定按钮显示的文字,父窗口为window(0是它自己)
	QPushButton button( "Hello world!", &window);
	button.resize( 100, 30 );//设置按钮的大小
	button.move(100, 100);//指定按钮位置

	//这里点击设置按钮则关闭程序
	QObject::connect(&button, SIGNAL(clicked()), &a, SLOT(quit()));

	button.show();//显示按钮,此处必须;如果window.show在后面就不用这个显示了
//	window.show();

	return a.exec();
}

