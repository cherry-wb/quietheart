#ifndef MYAPP_H
#define MYAPP_H
#include <QWidget>
class QKeyEvent;
class QCopChannel;
class MyApp : public QWidget
{
    Q_OBJECT
public:
    MyApp( QWidget *parent = 0, Qt::WFlags f = 0 );
    ~MyApp();

protected:
    virtual void keyPressEvent(QKeyEvent * event);
};

#endif
