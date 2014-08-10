/*一个最简单的让程序显示中文的方法。
*/
#include <QtGui/QApplication>
#include <QtGui/QLabel>
#include <QtCore/QTextCodec>
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	//QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
	QLabel label;
	label.setText(QObject::tr("同一个世界，同一个梦想！"));
	label.show();
	return app.exec();
}
