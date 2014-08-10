#include <QWidget>
#include <QPainter>
#include <iostream>
#include <QBitmap>
#include <QImage>
#include <QPicture>
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
	
	QPainter painter(this);//指定painter在this上面绘制

	//////QPixmap继承QPaintDevice,可直接指定载入Qt支持的文档,BMP、GIF、JPG、JPEG、PNG等.
	//如果图像大小和矩形不一样会自动缩放图像,它使用平台的绘图引擎,效果会根据平台而不同.
	QPixmap pixmap("./1.jpg");
	painter.drawPixmap (0,0,100,100,pixmap);//坐标(0,0)宽高(100,100)

	//////QBitmap是QPixmap的子类，用于绘制出来是单色图像。
	QBitmap bitmap("./1.jpg");
	painter.drawPixmap (200,0,100,100,bitmap);//绘制出来的结果是黑白的

	//////QImage使用Qt自身引擎绘制，不会因平台不同效果不同。
	//并且可以直接存取指定的像素.
	QImage image("./1.jpg");
	painter.drawImage (QRect(400,0,100,100),image );//绘制出来的结果是黑白的
	//painter.drawImage (200,0,image );//这样不缩放了

	//////QPicture是绘图装置，可以存，绘制的内容到文件也可读取。
	//存绘制的内容到文件中
	QPicture picture1;
	QPainter paintP1;
	paintP1.begin(&picture1); 
	paintP1.drawRect(0, 200, 100, 100);
	paintP1.end();
	picture1.save("draw_record.pic");
	//读取以前绘制的内容(效果类似于重播)
	QPicture picture2;
	picture2.load("draw_record.pic");  
	QPainter paintP2;
	paintP2.begin(this);
	paintP2.drawPicture(0, 0, picture2);//将在0,200处绘制一个矩形，不会覆盖前面的
	paintP2.end(); 

	//////其他
	QPixmap pixmap2("./big.gif");//gif实践之后发现不能动画
	painter.drawPixmap (200,200,100,100,pixmap2);

}
