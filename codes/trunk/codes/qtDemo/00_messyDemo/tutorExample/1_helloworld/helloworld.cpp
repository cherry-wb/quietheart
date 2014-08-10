/* 程序功能：只有一个helloworld按钮的程序。
 * 编译过程：
 * $qmake -project
 * $qmake
 * $make
 * 在X窗口运行的时候可以尝试用-geometry 100x200+10+20来指定大小试试。
 * */
#include <qapplication.h>
#include <qpushbutton.h>
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	//指定按钮显示的文字,父窗口为0也就是它自己那个窗口,这样这个按钮成为顶层窗口
	QPushButton hello( "Hello world!", 0 );

	//设置按钮的大小
	hello.resize( 100, 30 );
	//设定程序的主窗口为刚才那个按钮
	a.setMainWidget( &hello );
	hello.show();
	return a.exec();
}

