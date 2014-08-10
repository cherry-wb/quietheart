/* 程序功能：在Qt中显示中文等多字节字符,包括：
 * 存储自己设计的中文字符
 * 读取并存储文件中的中文字符
 * 将中文字符在终端中打印出来
 * 将中文字符直接显示到构件上面
 *
 * 注意，不太清楚中文字符的格式，好像是UTF8格式的中文字符,
 * 用$file test.txt应该可以查看test.txt的编码
 * *****************
 * 总结:
 * 1,获得utf8的QString:
 * 1)QString = QString::fromUtf8("***");
 * 2)QString = QObject::trUtf8("***");
 * 3)
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QString str = codec->toUnicode("1,哈哈哈");
 *
 * 2,将utf8的QString打印出来：
 * 1)QString str;
 * ...
 * QString str;
 * QByteArray byte = str.toUtf8();
 * cout<<byte.data();//const char*类型的。
 * 这里如果不是utf8的str则这样打印会有乱码。
 * */
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
	//设置整个程序的字体和编码
	//a.setFont(QFont("wenquanyi", 10));
	//a.setDefaultCodec(QTextCodec::codecForName("GBK"));//没有这个成员

	QWidget window;
	QHBoxLayout *hbox = new QHBoxLayout;

	//////存储并打印，显示自己输入的中文字符
	//首先是不可用的方法
	//QString input1("手动输入的");
	//cout<<"the CN character is :"<<input1.toUtf8().data()<<endl;//乱马
	//QLabel *label1 = new QLabel(input1);//乱马

	//这样初始化的QString是utf8的，可以直接传入QLabel不用trUtf8了(见后)。
	QString input1 = QString::fromUtf8("手动输入的");
	cout<<"the CN character is :"<<input1.toUtf8().data()<<endl;
	QLabel *label1 = new QLabel(input1);
	hbox->addWidget(label1);

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
		QLabel *label2 = new QLabel(QObject::trUtf8(byteLine.data()));
		hbox->addWidget(label2);
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
		QLabel *label3 = new QLabel(tmp);
		hbox->addWidget(label3);
	}
	//如果提前在QTextStream前关闭不行
	file.close();

	//////利用QTextCodec实现编码转换
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QString tmp2 = codec->toUnicode("1,哈哈哈");
	QLabel *label4 = new QLabel(tmp2);
	hbox->addWidget(label4);

	window.setLayout(hbox);
	window.show();

	return a.exec();
}

