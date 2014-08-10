#include <qlcdnumber.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include"lcdRange.h"
LCDRange::LCDRange( QWidget *parent, const char *name ): QWidget( parent, name )
{
	//QLCDNumber *lcd = new QLCDNumber( 2, this,  "lcd" );
	QLCDNumber *lcd = new QLCDNumber( 2 );
	lcd->setSegmentStyle(QLCDNumber::Filled);

	//slider = new QSlider( Horizontal, this, "slider" );
	slider = new QSlider( Horizontal);
	slider->setRange( 0, 99 );
	slider->setValue( 0 );

	//设置滑块为焦点代理。当想要给LCDRange一个键盘焦点，滑块就会注意到它。
	setFocusProxy( slider );

	//这里把slider的valueChanged信号分别连接到display和自定义的valueChanged上面
	connect( slider, SIGNAL(valueChanged(int)), lcd,
			SLOT(display(int)) );

	//这里两种方式实现信号的连接，利用标准信号发出自定义信号。
	//connect( slider, SIGNAL(valueChanged(int)),
	//		SIGNAL(valueChanged(int)) );
	connect( slider, SIGNAL(valueChanged(int)), this,
			SIGNAL(valueChanged(int)) );

	//这里利用另外的方式实现添加到VBox，而不用继承QVBox类
	Q3VBoxLayout *layout = new Q3VBoxLayout;
	layout->addWidget(lcd);
	layout->addWidget(slider);
	setLayout(layout);

}
int LCDRange::value() const
{
	return slider->value();
}
void LCDRange::setValue( int value )
{
	slider->setValue( value );
}
void LCDRange::setRange( int minVal, int maxVal )
{
	if ( minVal < 0 || maxVal > 99 || minVal > maxVal ) {
		//qWarning()是一个像printf一样的函数，默认情况下它的输出发送到stderr。
		//如果你想改变,可以使用::qInstallMsgHandler()函数安装自己的处理函数。
		qWarning( "LCDRange::setRange(%d,%d)\n"
				"\tRange must be 0..99\n"
				"\tand minVal must not be greater than maxVal",
				minVal, maxVal );
		return;
	}
	slider->setRange( minVal, maxVal );
}

