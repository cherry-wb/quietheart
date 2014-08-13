/* 程序功能：窗口内有一排按钮每个按钮对应一个数字，最左边和最右面是箭头。
 * 点击箭头更新主窗口的按钮标签,类似输入法选择输入汉字时候的选择列表.
 * */
#include <QApplication>
#include <QStringList>
#include "mySelectList.h"
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	QStringList listResult;
	listResult<<"first";
	listResult<<"second";
	listResult<<"third";
	listResult<<"forth";
	listResult<<"fifth";
	listResult<<"sixth";
	listResult<<"seventh";
	listResult<<"eighth";
	listResult<<"ninth";
	listResult<<"tenth";

	MySelectList pinyinTable;
	pinyinTable.setList(listResult);
	pinyinTable.refresh();
	pinyinTable.show();

	return a.exec();
}

