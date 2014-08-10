#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
class QListWidgetItem;
class QListWidget;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected slots:
	//for signal:itemClicked
		void clickedItem(QListWidgetItem *item);
		//还有其他的信号如下：
		//itemEntered,鼠标进入
		//itemDoubleClicked,双击
		//itemChanged,item数据改变
		//itemPressed,按下
		//itemSelectionChanged，选择的item变了
	
	private:
	QListWidget *listWidget;
	QListWidgetItem *item1;
	QListWidgetItem *item2;
	QListWidgetItem *item3;
};
#endif
