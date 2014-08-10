/*程序功能：多个部件组成的自定义部件。
 * 点击按钮可以关闭程序，可以拖动滑动条，滑动条的值显示在另外一个构件上面.
 * */
#include <qapplication.h>
#include <qpushbutton.h>
#include <qslider.h>
#include <qlcdnumber.h>
#include <qfont.h>
#include <q3vbox.h>
class MyWidget : public Q3VBox
{
	public:
		MyWidget( QWidget *parent=0, const char *name=0 );
};
MyWidget::MyWidget( QWidget *parent, const char *name )
: Q3VBox( parent, name )
{//继承了QVBox
	QPushButton *quit = new QPushButton( "Quit", this, "quit" );
	quit->setFont( QFont( "Times", 18, QFont::Bold ) );
	connect( quit, SIGNAL(clicked()), qApp, SLOT(quit()) );

	//这个是一个类似lcd显示屏幕的构建可以显示数字，设置显示2位
	QLCDNumber *lcd  = new QLCDNumber( 2, this, "lcd" );

	//一个类似滑动条的构建,不要忘记了Horizontal前面的"Qt::"
	QSlider * slider = new QSlider(Qt::Horizontal, this, "slider" );
	//设置slider的范围2位数以内，防止lcd构件显示溢出
	slider->setRange( 0, 99 );
	slider->setValue( 0 );
	
	//slider的value变化，会调用lcd的display显示出来。
	connect( slider, SIGNAL(valueChanged(int)), lcd,
			SLOT(display(int)) );
}
int main( int argc, char **argv )
{
	QApplication a( argc, argv );
	MyWidget w;
	a.setMainWidget( &w );
	w.show();
	return a.exec();
}

