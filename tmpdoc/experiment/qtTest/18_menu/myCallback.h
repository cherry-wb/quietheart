#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
class QMenuBar;
class QAction;
class QMenu;
class QPushButton;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected slots:
		//单击相应菜单项的响应函数
		void do1(void);
		void do2(void);
		void do3(void);

		void isChecked(bool);
	protected:
		void contextMenuEvent(QContextMenuEvent *event);
	private:
		//菜单栏
		QMenuBar *menuBar;

		//菜单项相关对象（包括动作，图标，标签文本等）
		QAction *action1;
		QAction *action2;
		QAction *action3;

		//单级菜单
		QMenu *singleMenu;

		//多级菜单
		QMenu *multiMenu;
		QMenu *subMenu1;
		QMenu *subMenu2;

		//按钮
		QPushButton *btn;
};
#endif
