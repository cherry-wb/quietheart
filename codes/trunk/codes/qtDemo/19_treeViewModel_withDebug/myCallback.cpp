#include "myCallback.h"
#include <QString>
#include <QTreeView>
#include <QDirModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtDebug>

//参考：http://www.kuqin.com/cpluspluslib/20071113/2318.html
//#include <QAbstractItemView>
#include <iostream>
/* XPM */
static const char * const pix_xpm[] = {
	"16 13 2 1",
	" 	c None",
	"#	c #000000000000",
	"    #   #     # ",
	"    #    #   #  ",
	"    #           ",
	"  ##### ####### ",
	"    #    #   #  ",
	"    #    #   #  ",
	"    ###  #   #  ",
	"  ###  ######## ",
	"    #    #   #  ",
	"    #    #   #  ",
	"    #   #    #  ",
	"    #  #     #  ",
	"  ### #      #  "};

MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	QIcon icn = QIcon(QPixmap((const char **)pix_xpm));//先建立一个图标 
	treeView = new QTreeView(this);
#if 0
	//QDirModel维护相关的目录内容的信息，它本身不持有数据，
	//仅是对本地文件系统中的文件与目录的描述。
	QDirModel *model = new QDirModel;
	treeView->setModel(model);
	//配置一个view去显示model中的数据，只需要简单地调用setModel()
	//setRootIndex()告诉views显示哪个目录的信息，这需要提供一个model index,然后用这个
	//model index去model中去获取数据
	//index()这个函数是QDirModel特有的，通过把一个目录做为参数，得到了需要的model index
	//其他的代码只是窗口show出来,进入程序的事件循环就好了
	treeView->setRootIndex(model->index(QDir::currentPath()));
#else
	//4行，1列
	//如果是多行多列的话，那么也只能显示第一列，多列是给QTableView用的.
	//QStandardItemModel *model = new QStandardItemModel(4,1,this);
	//model->setItem(row,column,item);//对于table用这个
	//QStandardItemModel model;
	QStandardItemModel *model = new QStandardItemModel(this);
	QStandardItem *parentItem = model->invisibleRootItem();
	for (int i = 0; i < 4; ++i)
	{
		QStandardItem *item = new QStandardItem(QString("item %0").arg(i));
		item->setEditable(false);//默认是可以编辑文字的
		//item->setIcon(icn);//设置的图标将在左面显示
		parentItem->appendRow(item);
		parentItem = item;
	}
	////////////
	treeView->setModel(model);//设置treeView的显示对象
	treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	//链接点击treeView上面东西的信号
	connect(treeView,SIGNAL(clicked(const QModelIndex &)),
		this,SLOT(clickedItem(const QModelIndex &)));
#endif
}
void MyCallback::clickedItem(const QModelIndex &index)
{
	//获取treeView上面的model(需要转换一下)
	QStandardItemModel *model = dynamic_cast<QStandardItemModel*>(treeView->model());

	//获取指定位置的item(model上面的指定位置使用了QModelIndex对象)
	QStandardItem *item = model->itemFromIndex(index);
	qDebug()<<"Clicked at"<<item->text();
}
