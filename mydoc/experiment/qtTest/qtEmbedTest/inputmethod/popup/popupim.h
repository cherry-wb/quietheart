#include <qwidget.h>

class PopupIM : public QWidget
{//输入法相关的类
    Q_OBJECT
public:
    PopupIM(QWidget *parent, const char *name = 0, int flags = 0);
    ~PopupIM();

signals:
    void keyPress( ushort unicode, ushort keycode,
	    ushort modifiers, bool press, bool repeat );
};
