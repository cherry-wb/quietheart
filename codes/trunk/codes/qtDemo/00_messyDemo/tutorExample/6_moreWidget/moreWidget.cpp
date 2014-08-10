/*程序功能：一个创建了许多构建的复杂的程序
 * 许多活动条连接了相应它的值的显示构件。
 * */
#include <qapplication.h>
#include <qpushbutton.h>
#include <qslider.h>
#include <qlcdnumber.h>
#include <qfont.h>
#include <q3vbox.h>
#include <q3grid.h>
using Qt::Horizontal;
class LCDRange : public Q3VBox
{
	public:
		LCDRange( QWidget *parent=0, const char *name=0 );
};

LCDRange::LCDRange( QWidget *parent, const char *name )
: Q3VBox( parent, name )
{
	QLCDNumber *lcd = new QLCDNumber( 2, this,  "lcd" );
	QSlider * slider = new QSlider(Horizontal, this, "slider" );
	slider->setRange( 0, 99 );
	slider->setValue( 0 );
	connect( slider, SIGNAL(valueChanged(int)), lcd,
			SLOT(display(int)) );
}
class MyWidget : public Q3VBox
{
	public:
		MyWidget( QWidget *parent=0, const char *name=0 );
};
	MyWidget::MyWidget( QWidget *parent, const char *name )
: Q3VBox( parent, name )
{
	QPushButton *quit = new QPushButton( "Quit", this, "quit" );
	quit->setFont( QFont( "Times", 18, QFont::Bold ) );
	connect( quit, SIGNAL(clicked()), qApp, SLOT(quit()) );

	//这里建立一个grid，可以添加四列构件
	//循环中的r和c无论谁是3和4只要乘积12那么添加之后结果就是三行4列的构件集
	Q3Grid *grid = new Q3Grid( 4, this );
	for( int r = 0 ; r < 3 ; r++ )
		for( int c = 0 ; c < 4 ; c++ )
			(void)new LCDRange( grid );
}
int main( int argc, char **argv )
{
	QApplication a( argc, argv );
	MyWidget w;
	a.setMainWidget( &w );
	w.show();
	return a.exec();
}

