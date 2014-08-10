#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
class QTableWidget;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected slots:
	//for signal:cellClicked
		void cellClick(int,int);
	//for signal:cellEntered
		void cellEnter(int,int);
	//其他信号包括
	//currentCellChanged(int currentRow,int currentColumn,int previousRow,int previousColumn);cell切换的信号
	//cellChanged ( int row, int column );//cell数据变化的信号
	//还有双击，按下，激活等等
	
	private:
	//QListWidget *listWidget;
	//QListWidgetItem *item1;
	//QListWidgetItem *item2;
	//QListWidgetItem *item3;
	QTableWidget *tableWidget;
};
#endif
