#ifndef __CANNON_H
#define __CANNON_H
#include <qwidget.h>
#include <QTimer>
//Added by qt3to4:
#include <QPaintEvent>
class CannonField : public QWidget
{
	Q_OBJECT
	public:
		CannonField( QWidget *parent=0, const char *name=0 );
		int angle() const { return ang; }
		QRect shotRect() const;
		QRect cannonRect() const;
		void paintCannon(QPainter &painter);
		void paintShot( QPainter &p );

		//int   force() const { return f; }
		//void  setForce( int newton );
		//void  forceChanged( int );
	//	QSizePolicy sizePolicy() const;
	public:
		int ang;
		int timerCount;
		QTimer * autoShootTimer;
		float shoot_ang;

		//int f;
	public slots:
			void setAngle( int degrees );
			void  shoot();
			void  moveShot();

signals:
	//这个函数不用实现
		void angleChanged( int );
	protected:
		//窗口部件刷新自己，这个虚函数就被Qt调用。
		////绘图工作都应该在paintEvent中完成
		void paintEvent( QPaintEvent * );
		void  paintShot( QPainter * );

};
#endif
