/*程序功能：
 * 给label添加一个链接，可以打开网址。
 * */
#include <QApplication>
#include <QLabel>
#include <QString>

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	QWidget window;

	QLabel label(&window);
	
	//这句话必须有，否则光有链接无法打开
	label.setOpenExternalLinks(true);
	QString strURL1 = "<a href=http://www.google.com>google</a>";
	label.setText(strURL1);

	window.show();
	return app.exec();
}
