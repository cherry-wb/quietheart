#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class EPushLabel;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
	MyCallback(QWidget *parent = 0);

	public slots:
	void labelPush();

	private:
	EPushLabel *m_label;
};

//自定义的push label
class EPushLabel:public QLabel
{
	Q_OBJECT
	public:
		EPushLabel(const QString &text, QWidget *parent = 0, Qt::WindowFlags f = 0);
	signals:
		//void pressSignal(ClickLabel*);
		void pressSignal();
	protected:
		void mousePressEvent(QMouseEvent *event);
};
#endif
