#ifndef __CANNON_H
#define __CANNON_H
#include <qwidget.h>
//Added by qt3to4:
#include <QPaintEvent>
class CannonField : public QWidget
{
	Q_OBJECT
	public:
		CannonField( QWidget *parent=0, const char *name=0 );
		int angle() const { return ang; }
	//	QSizePolicy sizePolicy() const;
	public:
		int ang;
	public slots:
			void setAngle( int degrees );

signals:
	//这个函数不用实现
		void angleChanged( int );
	protected:
		//窗口部件刷新自己，这个虚函数就被Qt调用。
		void paintEvent( QPaintEvent * );
};
#endif
