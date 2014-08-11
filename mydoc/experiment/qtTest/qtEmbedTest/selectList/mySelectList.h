#ifndef __MYSELECT_H
#define __MYSELECT_H
#include <QWidget>

#ifndef PAGECOUNT
#define PAGECOUNT 3
#endif
class QHBoxLayout;
class QPushButton;
class QStringList;
class MySelectList:public QWidget
{
	Q_OBJECT
	public:
		MySelectList(QWidget *parent = 0);
		void refresh();
		void setList(const QStringList &);
	protected slots:
		const QString selBtn(const QString &);

	private:
	//设置第i个按钮的标签为s
		void setText(int i,QString s);
	private:
	QHBoxLayout *hbox;

	//翻页
	QPushButton *btnNext;
	QPushButton *btnPrev;
	//btn数组
	QPushButton *btn[PAGECOUNT];

	//结果列表
	QStringList resultList;
	//当前页
	int pg;
	//一页的数目
	int pn;
};
#endif
