/*程序功能：在qt/e下面显示中文字体
 * 中文字体的显示在qt下面已经做了，但是在qt/e下面还没有做。
 * 这里实现了在qt/e下面显示中文字符。
 * 关键首先要有字体，其次在程序代码中设置已有的字体。
 * 然后就类似了。
 * 这里利用了5种方法。
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

	//这句话很重要，设置字体的要不显示不了中文
	//前提要将wenquanyi或者unifont相关字体找到，放到QTEDIR/lib/fonts里面
	a.setFont(QFont("wenquanyi", 10));
	//a.setFont(QFont("unifont", 10));


	QWidget window;
	QHBoxLayout *hbox = new QHBoxLayout;

	//////存储并打印，显示自己输入的中文字符
	//这样初始化的QString是utf8的，可以直接传入QLabel不用trUtf8了(见后)。
	QString input1 = QString::fromUtf8("手动输入的");
	cout<<"the CN character is :"<<input1.toUtf8().data()<<endl;
	QLabel *label1 = new QLabel(input1);
	hbox->addWidget(label1);

	QLabel *label2;
	label2 = new QLabel(QString::fromLocal8Bit("背光亮度设置"));
	hbox->addWidget(label2);

	//////直接读取文件并打印，显示文件中的中文字符
	QFile file("./test.txt");
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return 1;
	}
	if(!file.atEnd())
	{
		QByteArray byteLine = file.readLine();
		cout<<"the CN character read directly by file is:"
			<<byteLine.data()<<endl;
		//必须用QObject::trUtf8来显示utf8的中文字符(tr不行)。
		//QObject::trUtf8返回QString类型
		QLabel *label3 = new QLabel(QObject::trUtf8(byteLine.data()));
		hbox->addWidget(label3);
	}

	//////通过流读取文件并打印，显示文件中的中文字符
	QTextStream in(&file);
	if(!in.atEnd())
	{
		QString str = in.readLine();
		//这里str.toUtf8()返回的是QByteArray类型
		cout<<"the CN character read by stream file is:"
			<<str.toUtf8().data()<<endl;
		//"翻译"好作为Utf8的字符，传入tmp
		QString tmp = QObject::trUtf8(str.toUtf8().data());
		QLabel *label4 = new QLabel(tmp);
		hbox->addWidget(label4);
	}
	//如果提前在QTextStream前关闭不行
	file.close();

	//////利用QTextCodec实现编码转换
	//QTextCodec *codec = QTextCodec::codecForName("utf8");
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
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

