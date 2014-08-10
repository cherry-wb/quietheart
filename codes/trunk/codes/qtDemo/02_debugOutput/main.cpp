/*程序功能：测试qt下的调试输出功能。
 * 在Qt中，最好用QDebug的调试输出功能,它将输出到stderr上。
 * 更多信息参见：
 * http://qt.nokia.com/doc/4.6/debug.html
 * 这里不多说了。
*/
#include <QtDebug> 
#include <QRect>
#include <iostream>
using std::cout;
using std::endl;
void myOutput(QtMsgType type, const char *msg)
{
	switch (type) {
		case QtDebugMsg:
			cout<<"debug message!"<<endl;//删掉这句所有后面qDebug将无用。
			cout<<"the message is:"<<msg<<endl;//这是传给qDebug()的消息
			break;
		case QtWarningMsg:
			break;
		case QtCriticalMsg:
			break;
		case QtFatalMsg:
			abort();
	}
}

int main(int argc, char *argv[])
{
	//这个功能会自动地在各个项插入空格，最后自动地输出回车
	qDebug()<<"begin to"<<"out put the debug information!";

	//qDebug()还可以直接输出许多的Qt类
	QRect r(10,10,200,200);
	qDebug()<<"see the rect:"<<r;

	//还可以支持c风格的输出,这样的使用不用包含QtDebug文件
	qDebug("the value is %d", 6);

	//自定义输出
	qInstallMsgHandler(myOutput);//返回之前的输出处理函数
	qDebug()<<"my own!";//这样"my own"不会先打印，它做为myOutput中的一个参数。

	//恢复debug输出
	qInstallMsgHandler(0);
	qDebug()<<"restore the debug message";
	
	return 0;
}
