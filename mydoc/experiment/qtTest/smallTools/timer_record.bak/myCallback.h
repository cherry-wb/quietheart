#ifndef __MYCALLBACK_H
#define __MYCALLBACK_H
#include <QWidget>
class QScrollArea;
class QVBoxLayout;
class QLabel;
class QPushButton;
class QTimer;
class QLCDNumber;
class MyCallback:public QWidget
{
	Q_OBJECT
	public:
		MyCallback(QWidget *parent = 0,Qt::WindowFlags f = 0);
		void createTimeList(void);
	protected slots:
		void timeUpdate(void);
		void timeRecord(void);
		void timePause(void);
		void timeClear(void);
	private:
		QTimer *m_timer;
		int m_timerCnt;

		QLCDNumber *m_display;

		QScrollArea *m_sa;
		QVBoxLayout *m_saVbox;
		QWidget *m_saWidget;
		int m_recordCnt;

		QPushButton *m_recordBtn;
		QPushButton *m_pauseBtn;
		QPushButton *m_clearBtn;
};
#endif
