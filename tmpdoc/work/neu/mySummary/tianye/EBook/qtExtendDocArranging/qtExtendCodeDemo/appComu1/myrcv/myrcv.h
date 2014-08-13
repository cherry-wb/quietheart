#ifndef MYAPP_H
#define MYAPP_H
#include <QWidget>
class QKeyEvent;
class QCopChannel;
class MyRcv : public QWidget
{
    Q_OBJECT
public:
    MyRcv( QWidget *parent = 0, Qt::WFlags f = 0 );
    ~MyRcv();

protected slots:
	void processRcv(const QString&,const QByteArray&);
protected:
    virtual void keyPressEvent(QKeyEvent * event);
    private:
	QCopChannel *channel;
};

#endif
