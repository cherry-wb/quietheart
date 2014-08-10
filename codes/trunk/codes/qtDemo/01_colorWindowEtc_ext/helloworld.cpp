/* 程序功能：设置窗口的背景颜色，背景图像，背景透明度等常见属性
 * */
#include <QApplication>
#include <QWidget>
#include <QDir>
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	//设置全局的颜色（深蓝）
	QApplication::setPalette(QPalette(QColor( 0, 0, 50)));

//////////window1
	QWidget window1;

	//设置大小和位置位置(0,0)，宽高(320,480).
	window1.setGeometry(0,0,320,480);
	window1.show();

	//设置自己背景颜色,两种方法,用第一种
	window1.setPalette(QPalette(QColor( 0, 150, 50)));//绿色
	window1.setAutoFillBackground (true);//自己背景必须有这句,顺序无所谓
	//window1.setStyleSheet("background-color: red;");//只用这一句话也可以设置背景
	//window1.setStyleSheet("background-color: #FFFFFF;");//只用这一句话也可以设置背景

//////////window2
	QWidget window2;

	//位置
	window2.move(330,0);//移动窗口到(330,0)

	//固定大小,参数分别是宽和高,设置之后无法拖动改变窗口大小了
	window2.setFixedSize(320,480);//设置窗口的固定大小（将覆盖layout的自动设置）

	//设置半透明
	//QColor的第四个参数默认255是不透明
	//window2.setPalette(QPalette(QColor( 0, 0, 150,0)));//半透明色,不好用？好像只是"颜色"透明
	//window2.setPalette(QPalette(QColor( 0, 0, 0, 0)));//这样最大化窗口就会显示桌面了
	window2.setPalette(QPalette(QColor( 0, 200, 0)));
	window2.setAutoFillBackground (true);//自己背景必须有这句,顺序无所谓
	//设置窗口为半透明,默认为范围是0-1.0,默认1.0不透明
	window2.setWindowOpacity(0.8);
	
	//setAttribute用来设置和清除属性，第二参数为true表示设置，这也是默认值
	//设置鼠标事件透明，这样当鼠标点击的时候好像该部件不存在一样。
	window2.setAttribute(Qt::WA_TransparentForMouseEvents,true);//不管用？
	//这个属性设置无背景，即让窗口背景成为弹出该窗口之前的样子像透过似的
	//window2.setAttribute(Qt::WA_NoSystemBackground);
	window2.show();

/////////////window3
	QWidget window3;
	window3.setGeometry(0,490,320,480);

	//设置窗口的背景图片
	QPalette pal;
	QString filename = QDir::currentPath()+ "/1.jpg";
	//QString filename = "./1.jpg";//这也行
	QPixmap pixmap(filename);
	pal.setBrush(QPalette::Window,QBrush(pixmap));//第一个参数是ColorRole表示填充类型如前景背景等等
	window3.setPalette(pal);
	window3.show();

	return a.exec();
}

