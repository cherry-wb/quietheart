#ifndef _XIMEWINDOW_H_7c8d7829c7s6c8_
#define _XIMEWINDOW_H_7c8d7829c7s6c8_

#include <QWidget>

struct XData;
struct XWindowPrivate;


class XWindow : public QWidget
{
    Q_OBJECT

public:
    XWindow(const XData&, QWidget* parent = 0);
    virtual ~XWindow();


protected:
    virtual void paintEvent(QPaintEvent*);

private:
	//设置主界面
    void layout();

private:
	//用户输入和处理后的输出
    XWindowPrivate* mpdata;
};

//-------------------------------------------------------
#endif // _XIMEWINDOW_H_7c8d7829c7s6c8_
