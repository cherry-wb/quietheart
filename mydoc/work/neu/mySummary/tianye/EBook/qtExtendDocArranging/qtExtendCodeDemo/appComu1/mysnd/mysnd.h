#ifndef MYAPP_H
#define MYAPP_H
#include <QWidget>
class QKeyEvent;
class MySnd : public QWidget
{
    Q_OBJECT
public:
    MySnd( QWidget *parent = 0, Qt::WFlags f = 0 );
    ~MySnd();
    
protected slots:
	void clickResp();

protected:
    virtual void keyPressEvent(QKeyEvent * event);
};

#endif
