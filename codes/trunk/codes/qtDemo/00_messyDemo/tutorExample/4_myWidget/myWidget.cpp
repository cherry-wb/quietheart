/*程序功能：这里自定义了一个自己的构件，构件的包含一个按钮。
 *
 * */
#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
class MyWidget : public QWidget
{
	public:
		MyWidget( QWidget *parent=0, const char *name=0 );
};
MyWidget::MyWidget( QWidget *parent, const char *name )
: QWidget( parent, name )
{//这里name是给窗口部件分配的一个名称便于以后查找，它和显示文字无关
	//这里设定最大和最小大小,这样设置导致窗口大小固定
	setMinimumSize( 200, 120 );
	setMaximumSize( 200, 120 );

	//Qt可以跟踪这个局部变量，并且自动析构它。
	QPushButton *quit = new QPushButton( "Quit", this, "quit" );

	quit->setGeometry( 62, 40, 75, 30 );
	quit->setFont( QFont( "Times", 18, QFont::Bold ) );

	//这里,myWidget不知道应用程序的对象，所以用qApp它是程序的指针别名
	//需和应用程序对象对话时，Qt提供了一个别名qApp,这样不用特意建立对象了。
	connect( quit, SIGNAL(clicked()), qApp, SLOT(quit()) );
}
int main( int argc, char **argv )
{
	QApplication a( argc, argv );
	MyWidget w;
	w.setGeometry( 100, 100, 200, 120 );
	a.setMainWidget( &w );
	w.show();
	return a.exec();
}

