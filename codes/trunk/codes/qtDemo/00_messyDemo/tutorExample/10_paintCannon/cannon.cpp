#include"cannon.h"
//Added by qt3to4:
#include <QPainter>
#include <QPaintEvent>
//Added by qt3to4:
#include <QPixmap>
CannonField::CannonField( QWidget *parent, const char *name ): QWidget( parent, name )
{
	ang = 45;
//	f = 0;

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
	//repaint();

	//使用这个函数也可以，那就不必使用repaint()了。
	//update();
	
	//只重画窗口部件中含有加农炮的一小部分。FALSE参数说明在一个绘画事件发送到窗口部件之前指定的矩形将不会被擦去。这将会使绘画过程加速和平滑。 
	repaint( cannonRect(), FALSE );
	
	//update(cannonRect());

	//利用宏emit来发射angleChanged()信号
	emit angleChanged( ang );
}
/*
void CannonField::setForce( int newton )
{
	if ( newton < 0 )
		newton = 0;
	if ( f == newton )
		return;
	f = newton;
	emit forceChanged( f );
}*/
QRect CannonField::cannonRect() const
{
	//创建一个50*50大小的矩形，然后移动它，使它的左下角和窗口部件的左下角相等。 
	QRect r( 0, 0, 50, 50 );
	r.moveBottomLeft( rect().bottomLeft() );
	return r;
}
void CannonField::paintEvent( QPaintEvent *e )
{
	QString s = "Angle = " + QString::number( ang );
	//绘制字符串
	QPainter p( this );
	p.drawText( 200, 200, s );
	
	//绘制一个图形
	//设置用画刷填充图形为蓝色
	p.setBrush(Qt::blue );
	//这个设置绘制边界画笔为在边界上面什么也不画，无边框
	//p.setPen( Qt::NoPen );
	//转换painter系统的坐标原点为窗口的左下角(0,0),坐标轴方向不变（所以y恒负了）
	p.translate( 0, rect().bottom() );
	//这里绘制一个1/4的圆（90度），是顺时针的，角度度量为1度的1/16所以要*16
	p.drawPie( QRect(-35, -35, 70, 70), 0, 90*16 );
	//p.drawPie( QRect(-35, -35, 35,35 ), 0, 90*16 );
	//绕QPainter坐标系统的初始位置旋转它ang浮点
	p.rotate( -ang );
	//在圆上绘制一个矩形（类似炮筒）
	p.drawRect( QRect(33, -4, 15, 8) );

	/*利用下面的代码利用pixmap绘制图形也可以*/
	/*
	//不太懂???
	if ( !e->rect().intersects( cannonRect() ) )
		return;

	//创建一个pixmap
	//绘画操作都在这个pixmap中完成，并且之后只用一步操作来把这个pixmap画到屏幕上
	//关于闪烁的本质教程说的不清晰???
	QRect cr = cannonRect();
	QPixmap pix( cr.size() );

	//用这个pixmap来充满这个窗口部件的背景
	pix.fill( this, cr.topLeft() );

	QPainter p( &pix );

	//绘制一个图形
	//设置用画刷填充图形为蓝色
	p.setBrush(Qt::blue );
	
	//这个设置绘制边界画笔为在边界上面什么也不画，无边框
	//p.setPen( Qt::NoPen );
	//转换painter系统的坐标原点为窗口的左下角(0,0),坐标轴方向不变（所以y恒负了）
	//p.translate( 0, rect().bottom() );
	
	p.translate( 0, pix.height() - 1 );
	//这里绘制一个1/4的圆（90度），是顺时针的，角度度量为1度的1/16所以要*16
	p.drawPie( QRect(-35, -35, 70, 70), 0, 90*16 );
	//p.drawPie( QRect(-35, -35, 35,35 ), 0, 90*16 );
	//绕QPainter坐标系统的初始位置旋转它ang浮点
	p.rotate( -ang );
	//在圆上绘制一个矩形（类似炮筒）
	p.drawRect( QRect(33, -4, 15, 8) );
	p.end();

	//画这个pixmap
	p.begin( this );
	p.drawPixmap( cr.topLeft(), pix );
	*/
}

