/* 程序功能：测试QGridLayout,4行，5列.
 * 其中前三行：
 * 只有第0列，2列，4列,0行，2行，有button.
 * 第1行的1，2，3列都是空白.
 * 其他是label.
 * 第四行(表示为3行):
 * 只有两个大按钮占据了整个一行。
 *
 * 主要实现的是：
 * 1）如何在QGridLayout指定的一个格中添加构件
 * 2）如何在QGridLayout中添加大的跨多个格的构件
 * 3）如何设置每个行，列的最小大小（注意只能行／列的设置不能设置某个格）
 * 4）实践发现：一个构件实际可以add多次，以最后一次为准。
 *
 *
 * 注意的是：空白的地方实际是QSpacerItem这个类，QSpacerItem就是用来提供layout中的空白的。
 * 一般不会直接用它，在该有的时候自动会有，调用下面函数的时候会改变其大小：
 * QHBoxLayout:addSpacing(), addStretch(), insertSpacing(), insertStretch()
 * QGridLayout:setRowMinimumHeight(), setRowStretch(), setColumnMinimumWidth(), setColumnStretch()
 * */
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <iostream>
using std::cout;
using std::endl;

void addButtons(QGridLayout *grid);
void addLabels(QGridLayout *grid);
void addBigButton(QGridLayout *grid);

int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	QWidget window;

	//建立GridLayout
	QGridLayout *grid = new QGridLayout;

	//////给grid添加多个button
	addButtons(grid);
	
	//////给grid添加多个彩色label(作为button和button之间的占位的边界)
	addLabels(grid);

	//////设置gridLayout的一些属性
	//设置第1列的最小宽度(列从0开始,列只有宽度)
	grid->setColumnMinimumWidth(1,64);
	//设置第1行的最小高度(行从0开始,行只有高度)
	grid->setRowMinimumHeight(1,50);
	//拉伸是什么意思？还不十分清楚??????相关注释摘抄如下：
	//列1是可拉伸的,左边的列不能拉伸的（因为它的拉伸因数是0，这是默认值），
	//QGridLayout就会在MyWidget被重新定义大小的时候试图让左面的窗口部件大小不变，
	//而重新定义右下角CannonField的大小。
	//grid->setColumnStretch(1,10);//???什么作用???

	//////添加两个大的按钮
	addBigButton(grid);

	//这里设置选用哪个布局
	window.setLayout(grid);
	window.show();
	return a.exec();
}

void addButtons(QGridLayout *grid)
{
	//建立button
	QPushButton *btn1 = new QPushButton("btn1");
	QPushButton *btn2 = new QPushButton("btn2");
	QPushButton *btn3 = new QPushButton("btn3");
	QPushButton *btn4 = new QPushButton("btn4");
	QPushButton *btn5 = new QPushButton("btn5");
	QPushButton *btn6 = new QPushButton("btn6");

	/*这里可以用
	  grid->setMargin(2);
	  grid->setSpacing(3);
	  来设置按钮的填充行为，例如填满整个单元格等。
	 * */
	//添加一个button,参数分别为控件，行，列，布局（默认为0）
	grid->addWidget(btn1,0,0,Qt::AlignCenter);//这样添加的，设置前面的填充变为无效
	grid->addWidget(btn2,0,2,Qt::AlignCenter);
	grid->addWidget(btn3,0,4,Qt::AlignCenter);
	grid->addWidget(btn4,2,0);//这样添加的，前面的填充效果起作用了
	grid->addWidget(btn5,2,2);
	grid->addWidget(btn6,2,4);

	cout<<"btn1 height:"<<btn1->height()<<endl;
	cout<<"btn1 width:"<<btn1->width()<<endl;
	cout<<"btn2 height:"<<btn1->height()<<endl;
	cout<<"btn2 width:"<<btn1->width()<<endl;
	cout<<"btn3 height:"<<btn1->height()<<endl;
	cout<<"btn3 width:"<<btn1->width()<<endl;
	cout<<"btn4 height:"<<btn1->height()<<endl;
	cout<<"btn4 width:"<<btn1->width()<<endl;
	cout<<"btn5 height:"<<btn1->height()<<endl;
	cout<<"btn5 width:"<<btn1->width()<<endl;
	cout<<"btn6 height:"<<btn1->height()<<endl;
	cout<<"btn6 width:"<<btn1->width()<<endl;
}

void addLabels(QGridLayout *grid)
{
	QLabel *label1 = new QLabel("1");
	label1->setPalette(QPalette(QColor( 0, 0, 50)));//设置背景色
	label1->setAutoFillBackground (true);//必须有这句,顺序无所谓

	//QLabel *label2 = new QLabel("2");
	//label2->setPalette(QPalette(QColor( 0, 0, 50)));//设置背景色
	//label2->setAutoFillBackground (true);//必须有这句,顺序无所谓

	//QLabel *label3 = new QLabel("3");
	//label3->setPalette(QPalette(QColor( 0, 0, 50)));//设置背景色
	//label3->setAutoFillBackground (true);//必须有这句,顺序无所谓

	//QLabel *label4 = new QLabel("4");
	//label4->setPalette(QPalette(QColor( 0, 0, 50)));//设置背景色
	//label4->setAutoFillBackground (true);//必须有这句,顺序无所谓

	QLabel *label5 = new QLabel("5");
	label5->setPalette(QPalette(QColor( 0, 0, 50)));//设置背景色
	label5->setAutoFillBackground (true);//必须有这句,顺序无所谓

	QLabel *label6 = new QLabel("6");
	label6->setPalette(QPalette(QColor( 0, 0, 50)));//设置背景色
	label6->setAutoFillBackground (true);//必须有这句,顺序无所谓

	QLabel *label7 = new QLabel("7");
	label7->setPalette(QPalette(QColor( 0, 0, 50)));//设置背景色
	label7->setAutoFillBackground (true);//必须有这句,顺序无所谓

	QLabel *label8 = new QLabel("8");
	label8->setPalette(QPalette(QColor( 0, 0, 50)));//设置背景色
	label8->setAutoFillBackground (true);//必须有这句,顺序无所谓

	QLabel *label9 = new QLabel("9");
	label9->setPalette(QPalette(QColor( 0, 0, 50)));//设置背景色
	label9->setAutoFillBackground (true);//必须有这句,顺序无所谓

	grid->addWidget(label1,1,0);
	//grid->addWidget(label2,1,1);
	//grid->addWidget(label3,1,2);
	//grid->addWidget(label4,1,3);
	grid->addWidget(label5,1,4);
	grid->addWidget(label6,0,1);
	grid->addWidget(label7,0,3);
	grid->addWidget(label8,2,1);
	grid->addWidget(label9,2,3);
}
void addBigButton(QGridLayout *grid)
{
	QPushButton *bigBtn1 = new QPushButton("bigBtn1");
	QPushButton *bigBtn2 = new QPushButton("bigBtn2");

	//在第3行，第0列开始，添加一个跨度1行，2列的bigBtn1.
	grid->addWidget(bigBtn1, 3, 0, 1,2);
	
	//添加bigBtn2，注意这里可以添加两次，以最后一次为准
	grid->addWidget(bigBtn2, 3, 1, 1,3);//起始列为1则覆盖了bigBtn1的一部分
	grid->addWidget(bigBtn2, 3, 2, 1,3);//修正注意起始列为2
}
