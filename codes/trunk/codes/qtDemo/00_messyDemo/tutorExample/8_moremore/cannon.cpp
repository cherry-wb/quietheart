#include"cannon.h"
//Added by qt3to4:
#include <QPainter>
#include <QPaintEvent>
CannonField::CannonField( QWidget *parent, const char *name ): QWidget( parent, name )
{
	ang = 45;
	//设置了一个自定义调色板,说明背景色.
	setPalette( QPalette( QColor( 250, 250, 200) ) );

	//通过这句话来填充背景颜色否则背景颜色显示不出来
	setAutoFillBackground(true);
}
void CannonField::setAngle( int degrees )
{
	if ( degrees < 5 )
		degrees = 5;
	if ( degrees > 70 )
		degrees = 70;
	if ( ang == degrees )
		return;
	ang = degrees;

	//清空窗口部件（通常用背景色来充满）并向窗口部件发出一个绘画事件。
	//这样的结构就是调用窗口部件的绘画事件函数一次。
	repaint();

	//使用这个函数也可以，那就不必使用repaint了。
	//update();

	//利用宏emit来发射angleChanged()信号
	emit angleChanged( ang );
}
void CannonField::paintEvent( QPaintEvent * )
{
	QString s = "Angle = " + QString::number( ang );
	QPainter p( this );
	p.drawText( 200, 200, s );
}

