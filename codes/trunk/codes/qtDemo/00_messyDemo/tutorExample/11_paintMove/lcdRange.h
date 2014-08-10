#ifndef __LCDRANGE_H
#define __LCDRANGE_H
#include <qslider.h>
using Qt::Horizontal;
class LCDRange : public QWidget
{
	//如果使用信号和槽就必须要包含这个宏（该类必须是QObject类的子类）
	//之后就可以自定义信号和槽了。
	Q_OBJECT
	public:
		LCDRange( QWidget *parent=0, const char *name=0 );
		int value() const;

	public:
		QSlider *slider;
	public slots:
			//这里自定义槽
			void setValue(int);
			void setRange(int minVal, int maxVal);
signals:
		//这里自定义信号
		//一个类只能发送自己定义的或者继承过来的信号,这个函数不必实现它
		void valueChanged(int);

};
#endif
