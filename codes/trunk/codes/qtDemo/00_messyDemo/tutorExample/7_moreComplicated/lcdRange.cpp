#include <qlcdnumber.h>
#include"lcdRange.h"
LCDRange::LCDRange( QWidget *parent, const char *name ): Q3VBox( parent, name )
{
	QLCDNumber *lcd = new QLCDNumber( 2, this,  "lcd" );
	//QSlider * slider = new QSlider( Horizontal, this, "slider" );
	slider = new QSlider( Horizontal, this, "slider" );
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
