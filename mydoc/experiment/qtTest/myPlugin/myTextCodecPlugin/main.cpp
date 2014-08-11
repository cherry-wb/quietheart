/*程序功能：
 * 这个程序使用了自己定义的一个插件
 */
#include <QApplication>
#include <QWidget>
#include <QFile>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QTextStream>
#include <QTextCodec>
#include <iostream>
using std::cout;
using std::endl;
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	//a.setFont(QFont("wenquanyi", 10));
	//a.setFont(QFont("unifont", 10));


	QWidget window;
	QHBoxLayout *hbox = new QHBoxLayout;

	//////利用QTextCodec实现编码转换
	//QTextCodec *codec = QTextCodec::codecForName("utf8");
	QTextCodec *codec = QTextCodec::codecForName("MyCode1");
	//a.setDefaultCodec(codec);
	//QString tmp2 = codec->fromUnicode(QString::fromUtf8("哈哈"));
	QString tmp2 = codec->toUnicode("哈哈");
	//QTextCodec::setCodecForTr(codec);
	QLabel *label5 = new QLabel(tmp2);
	hbox->addWidget(label5);

	window.setLayout(hbox);
	window.show();

	return a.exec();
}

