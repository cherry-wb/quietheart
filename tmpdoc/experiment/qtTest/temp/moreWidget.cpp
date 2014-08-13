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
	//如果使用信号和槽就必须要包含这个宏（还要继承QObject类?）
//	Q_OBJECT
	Q_GADGET
	public:
		LCDRange( QWidget *parent=0, const char *name=0 );
		int value() const;
	public:
		QSlider *slider;
	public slots:
			//这里自定义槽
			void setValue(int);
signals:
		//这里自定义信号
		//一个类只能发送自己定义的或者继承过来的信号
		void valueChanged(int);
};

LCDRange::LCDRange( QWidget *parent, const char *name )
: Q3VBox( parent, name )
{
	QLCDNumber *lcd = new QLCDNumber( 2, this,  "lcd" );
	slider = new QSlider(Horizontal, this, "slider" );
	slider->setRange( 0, 99 );
	slider->setValue( 0 );
	connect( slider, SIGNAL(valueChanged(int)), lcd,
			SLOT(display(int)) );
	
	//这里把滑块的valueChanged信号和这个对象的valueChanged信号连接起来了
	//带有三个参数的connect函数会连接到this对象的信号或者槽
	//这个函数实现了拖动滑块发送滑块的valueChanged又进而"链接"的发送了对象的valueChanged自定义信号,所以实现了拖动滑块最终发送了自定义的信号
	connect( slider, SIGNAL(valueChanged(int)),
			SIGNAL(valueChanged(int)) );
}
int LCDRange::value() const
{
	return slider->value();
}
void LCDRange::setValue( int value )
{
	slider->setValue( value );
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
	Q3Grid *grid = new Q3Grid( 4, this );
	LCDRange *previous = 0;
	for( int r = 0 ; r < 4 ; r++ )
		for( int c = 0 ; c < 4 ; c++ )
		{
			LCDRange* lr = new LCDRange( grid );
			if ( previous )
			{
				//这里设置拖动后一个滑块会调用前一个滑块的setValue函数。
				connect( lr, SIGNAL(valueChanged(int)),
						previous, SLOT(setValue(int)) );
			}
			previous = lr;

		}
}
int main( int argc, char **argv )
{
	QApplication a( argc, argv );
	MyWidget w;
	a.setMainWidget( &w );
	w.show();
	return a.exec();
}

