#ifndef __MYSELECT_H
#define __MYSELECT_H
#include <QWidget>

#ifndef PAGECOUNT
#define PAGECOUNT 6
#endif
class QHBoxLayout;
class QPushButton;
class QStringList;
class MySelectList:public QWidget
{//选择列表,列出备选结果供选择（具有翻页功能）
	Q_OBJECT
	public:
		MySelectList(QWidget *parent = 0);
		//刷新备选列表显示
		void refresh();
		//设置列表显示的字符串链表
		void setList(const QStringList &);

		//获得每页的最多选项数目
		int getPn()const;
		//获得当前页
		int getPg()const;
		//获得第n个按钮对应的当前页结果字符
		QString getSelChar(int n);
		//获得按钮指针
		QPushButton *getNextBtn()const;
		QPushButton *getPrevBtn()const;
		//QPushButton **getBtnList();//注意获得这个程序后不要越界访问,报错？
		//btn数组
		QPushButton *btn[PAGECOUNT];

	public slots:
		const QString pageBtn(const QString &);

	private:
	//设置第i个按钮的标签为s
		void setText(int i,QString s);
	private:
	QHBoxLayout *hbox;

	//翻页
	QPushButton *btnNext;
	QPushButton *btnPrev;
	//btn数组
	//QPushButton *btn[PAGECOUNT];

	//结果列表
	QStringList resultList;
	//当前页
	int pg;
	//一页的数目
	int pn;
};
#endif
