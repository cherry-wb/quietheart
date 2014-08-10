#include <QWidget>
#include <QPainter>
#include <iostream>
#include "myCallback.h"
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	setMouseTracking(true);
}
void MyCallback::paintEvent( QPaintEvent * /*e*/ )
{
	using std::cout;
	using std::endl;
	cout<<"hi,in paintEvent!"<<endl;
	
	QPainter painter(this);

	//////划线，两种方法,用第2种
	//painter.drawLine(10,10,20,20);
	//QlineF中，F表示是浮点的
	QLineF line(10.0, 10.0, 20.0, 20.0);
	painter.drawLine(line);

	//////绘制弧线，两种方法,用第2种
	//度数应该乘以16,第一个是起点（相对3点处）第二个是绘制多少度。绘制方向逆时针
	//如果是矩形,360度就是椭圆正方形是正圆
	int startAngle0 = 0;
	int spanAngle0 = 90 * 16;
	//painter.drawArc(40,40,60,60, startAngle, spanAngle);
	QRectF rectangle0(160.0, 60.0, 20.0, 20.0);
	painter.drawArc(rectangle0, startAngle0, spanAngle0);

	//////划点，两种方法,用第2种
	//painter.drawPoint(160,160);
	QPoint point(160,160);
	painter.drawPoint(point);

	//////画矩形，两种方法，参数前两个是左上角，后两个是宽和高
	//painter.drawRect(20,20,40,40);
	QRectF rectangle(20.0, 20.0, 40.0, 40.0);
	painter.drawRect(rectangle);

	//////绘制扇形，两种方法,用第2种
	//度数应该乘以16,第一个是起点（相对3点处）第二个是绘制多少度。绘制方向逆时针
	//如果是矩形,360度就是椭圆正方形是正圆
	//painter.drawEllipse是画整个圆（椭圆）
	int startAngle = 0;
	int spanAngle = 120 * 16;
	//painter.drawPie(40,40,60,60, startAngle, spanAngle);
	QRectF rectangle1(40.0, 40.0, 60.0, 60.0);
	painter.drawPie(rectangle1, startAngle, spanAngle);

	//////绘制两个不同填充风格的填充矩形
	QBrush brush(Qt::SolidPattern);
	painter.setBrush(brush);
	painter.drawRect(150,150,10,10);

	painter.setBrush(Qt::Dense1Pattern);
	painter.drawRect(130,130,10,10);
	//////绘制文字，多种方法其中一种
	painter.drawText(100,100,tr("Test the text"));

}
