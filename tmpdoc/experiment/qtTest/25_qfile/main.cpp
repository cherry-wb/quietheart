/*程序功能：
 * 测试一个文件是否存在
 * */
#include <QApplication>
#include <QFile>
#include <QDebug>
int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	QFile f("/home/quietheart/test");
	if(f.exists())
	{//目录也是文件
		qDebug()<<"/home/quietheart/test :"<<"exists!";
	}
	else
	{
		qDebug()<<"/home/quietheart/test :"<<"not exists!";
	}
	//app.exec();
	return 0;
}
