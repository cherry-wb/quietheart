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

	//绘制一个图像,如果图像大小和矩形不一样会自动缩放图像
	//还有好多重载函数
	QPixmap pixmap("./1.jpg");
	painter.drawPixmap (300,300,100,100,pixmap );//坐标(300,300)宽高(100,100)
	//painter.drawPixmap(pixmap.rect(),pixmap);
	//drawPixmap ( int x, int y, int width, int height, const QPixmap & pixmap );

	//建立一个画笔，具有不同的绘制属性如颜色等
	QPen pen;  
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(6);
	pen.setBrush(Qt::green);
	//QColor(255,255,255,125);第四个参数是颜色的透明度，绘制的时候覆盖后面颜色的程度
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	//有两个设置画笔的重载函数，这里使用第一个
	painter.setPen(pen);
	//painter.setPen(Qt::SolidLine);//根据Qt::PenStyle来设置画笔

	//////划线，两种方法,用第2种
	//painter.drawLine(10,10,20,20);
	QLineF line(10.0, 10.0, 50.0, 50.0);
	painter.drawLine(line);

	//////画矩形，两种方法，参数前两个是左上角，后两个是宽和高
	//painter.drawRect(20,20,40,40);
	QRectF rectangle(60.0, 60.0, 100.0, 100.0);//有F后缀表示可以传入浮点型
	painter.drawRect(rectangle);
	
	//////绘制填充矩形
	//首先设置填充的方式
	QBrush brush(Qt::SolidPattern);
	brush.setColor(Qt::blue);//填充蓝色
	painter.setBrush(brush);
	painter.drawRect(150,150,100,100);

	//////绘制文字，多种方法其中一种
	//setFont函数可以设置字体
	painter.drawText(280,280,tr("Test the text\ngood!"));
	
	//另外一种建立painter的方法：
	//QPainter painter;//不再构造函数中指定绘制谁
	//painter.begin(将要绘制的对象);//参数和构造函数类似,这样后所有的pen等会成为默认
	//...绘制在将要绘制的对象上...
	//painter.end();//结束绘制，释放资源,实际析构的时候会调用end的。
	//painter.isActive();//表示没有end()过
	
	//旋转缩放的在另外一个例子里面这里省略,类似如下
	// QMatrix matrix;
	// matrix.translate(50, 50);
	// matrix.rotate(45);
	// matrix.scale(0.5, 1.0);
	// painter.setMatrix(matrix);

}
