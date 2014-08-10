#include "myCallback.h"
#include <QString>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QLabel>

//#include <QAbstractItemView>
#include <iostream>
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{

	//////建立一个tabel，
	//可以像第二种方式同时指定行列，这里采用第一种可以以后指定
	tableWidget = new QTableWidget(this);
	//tableWidget = new QTableWidget(12, 3, this);//创建时指定行列
	tableWidget->setRowCount(4);//指定为4行
	tableWidget->setColumnCount(5);//指定为5列

	//////添加内容
	//添加一个TableWidget
	QTableWidgetItem *newItem = new QTableWidgetItem("test");
	tableWidget->setItem(0, 0, newItem);//给第0行0列添加一个TableWidget
	//添加一个有图标的TableWidget
	//建立一个左侧图标的文字
	QTableWidgetItem *cubesHeaderItem = new QTableWidgetItem(tr("Cubes"));
	cubesHeaderItem->setIcon(QIcon(QPixmap("./background1.jpg")));//设置图标
	cubesHeaderItem->setTextAlignment(Qt::AlignVCenter);//设置文本对齐方式
	tableWidget->setItem(0, 1, cubesHeaderItem);//给第0行1列添加一个TableWidget

	//添加一个Widget
	QLabel *label = new QLabel("label!");
	tableWidget->setCellWidget(1,1,label);


	//////设置一些属性
	//设置当前的cell
	tableWidget->setCurrentCell(2,2);

	//设置第0列的顶部“标题”Widget。默认就是阿拉伯数字,其他列和行类似
	newItem = new QTableWidgetItem("hItem!");
	tableWidget->setHorizontalHeaderItem(0,newItem);

	//设置前三行的行头“标题标签”
	//实践发现如果标题数目超过行数目似乎是忽略后面的了。列的类似。
	QStringList strList;
	strList<<"first"<<"second"<<"third";//<<"forth"<<"fifth";
	tableWidget->setVerticalHeaderLabels(strList);

	//QTableWidgetItem *getItem = tableWidget->item(1,1);
	QTableWidgetItem *getItem = tableWidget->item(0,0);//获得指定位置的QTableWidgetItem
	getItem->setText("testGet");
	//////响应函数
	//点击表中某个方格的响应
	QObject::connect(tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(cellClick(int,int)));
	//鼠标光标进入的时候调用
	//默认得按着鼠标键进入才行，设置mouseTracking为true不用按鼠标键也行了见06_mouseEvent
	QObject::connect(tableWidget, SIGNAL(cellEntered(int,int)), this, SLOT(cellEnter(int,int)));
}

void MyCallback::cellClick(int row, int column)
{
	using std::cout;
	using std::endl;
	//获得item上面的字
	cout<<"clicked at:("<<row<<","<<column<<")"<<endl;
}
void MyCallback::cellEnter(int row, int column)
{
	using std::cout;
	using std::endl;
	//获得item上面的字
	cout<<"enter in:("<<row<<","<<column<<")"<<endl;
}
