#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>

//这里使用了两种使用treeView的方法，对于这个宏定义
//MY_DEBUG_MOD == 1表示用常用的model
//MY_DEBUG_MOD == 0是一个非常简单的QDirModel
class QTreeView;
class QModelIndex;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected slots:
		void clickedItem(const QModelIndex &index);
	private:
	QTreeView *treeView;
};
#endif
