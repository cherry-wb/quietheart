#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
#include <QWidgetAction>

class QMenu;
class QMouseEvent;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0);
	protected slots:
		void do1();
		void do2();
	protected:
		void mousePressEvent(QMouseEvent *);
	private:
		QMenu *m_menu;
};

class QLabel;
class QPushButton;
class MyCustomWidget:public QWidget
{
	Q_OBJECT
	public:
	MyCustomWidget(QWidget *parent = 0);

	signals:
	void triggleAction();

	protected slots:
		void clicked();

	private:
	QLabel *label;
	QPushButton *btn;
};

class MyWidgetAction:public QWidgetAction 
{
	Q_OBJECT
	public:
		MyWidgetAction(QObject*);
		QWidget* createWidget(QWidget*);
		protected slots:
			//这里定义菜单项的check相关信息,相应于toggle信号
			void changeCheckState(bool);
	private:
		MyCustomWidget* widget;
};
#endif
