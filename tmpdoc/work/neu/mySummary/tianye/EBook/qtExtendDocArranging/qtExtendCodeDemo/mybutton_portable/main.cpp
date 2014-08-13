#include <QWidget>
#include <QPushButton>
#include <qtopiaapplication.h>

#ifdef SINGLE_EXEC
QTOPIA_ADD_APPLICATION(QTOPIA_TARGET,examplemybutton)
#define MAIN_FUNC main_examplemybutton
#else
#define MAIN_FUNC main
#endif

QSXE_APP_KEY

int MAIN_FUNC( int argc, char **argv )
{
	QSXE_SET_APP_KEY(argv[0]);
	QtopiaApplication a( argc, argv );

	QTOPIA_SET_DOCUMENT_SYSTEM_CONNECTION();

	QWidget window;
	//window.resize(320, 240);
	a.setMainWidget(&window);
	a.showMainWidget();




	//指定按钮显示的文字,父窗口为window(0是它自己)
	QPushButton button( "Hello world!", &window);
	button.resize( 100, 30 );//设置按钮的大小
	button.move(100, 100);//指定按钮位置

	//这里点击设置按钮则关闭程序
	QObject::connect(&button, SIGNAL(clicked()), &a, SLOT(quit()));

	button.show();//显示按钮,此处必须;如果window.show在后面就不用这个显示了
	//	window.show();

	return a.exec();
}
