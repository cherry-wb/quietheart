/*程序功能：
 * 将一个按钮作为一个子窗口部件添加到一个布局类中
 * */
#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
//添加这个头文件，获得我们要使用的布局类QVBox
#include <q3vbox.h>
int main( int argc, char **argv )
{
	QApplication a( argc, argv );
	
	//这是一个布局类，把它的自窗口部件排成一个垂直的行，可以根据每一个自窗口部件的QWidget::sizePolicy()来安排空间。
	Q3VBox box;
	box.resize( 200, 120 );

	//这里建立一个按钮，并且设置它的父窗口部件为刚才的那个布局box
	QPushButton quit( "Quit", &box );
	quit.setFont( QFont( "Times", 18, QFont::Bold ) );

	QObject::connect( &quit, SIGNAL(clicked()), &a, SLOT(quit()) );
	a.setMainWidget( &box );
	
	//这里，当父窗口box被显示的时候，它会自动调用所有子窗口的显示函数。
	box.show();
	return a.exec();
}

