/*程序功能：
 * 一个list，每一条目包含：
 * 最左面“第一列”是一个图标
 * “第二列”是一个描述词
 * 最右面是一个数字
 * 第二列到最右面之间有大块的空白，且第二列到最右面有一个下划线。
 * 点击每一个条目都有响应。
 *
 * 总共可以显示8个条目。最上方有一个“标题栏”
 * */
#include <QApplication>
#include "mylist.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	//MyListItem *item1 = new MyListItem("filename", "text1",
	//				 "count");
	//item1->show();
	MyList list;
	list.setGeometry(10,10,100,100);
	list.show();
	int status = app.exec();
	//delete item1;
	return status;
}
