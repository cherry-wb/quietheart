//#include <qtopia/qpeapplication.h>
//#include <qmultilineedit.h>
//#include <qvbox.h>
#include <QApplication>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <popupim.h>


int main(int argc, char **argv) 
{
    QApplication a(argc, argv);

	QWidget window;
	//////垂直布局
    QVBoxLayout *vb = new QVBoxLayout;

	//////编辑框
    QTextEdit *mle = new QTextEdit;

	//////输入法
    PopupIM *pi = new PopupIM;
	//将输入法获取到的keyPress信号传到编辑框定义的处理按键的槽中
    //QObject::connect(pi, SIGNAL(keyPress(ushort, ushort, ushort, bool, bool)),
	 //   mle, SLOT(interpretKeyPress(ushort, ushort, ushort, bool, bool)));
	
	vb->addWidget(mle);
	vb->addWidget(pi);

	window.setLayout(vb);
	window.show();
	//QWSServer::setCurrentInputMethod(im);
    return a.exec();
}
