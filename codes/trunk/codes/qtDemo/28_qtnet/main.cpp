/*程序功能：
 * 一个简单的Qt网络编程的例子
 * 注意：
 * 1)编译的时候需要在.pro文件中加入：LIBS+=-lQtWebKit
 * 2)包含头文件的时候需要加上前缀QtNetwork
 *	#include <QtNetwork/QNetworkAccessManager>
 * 否则无法编译
 * 程序功能是：
 * 有一个输入框和一个按钮。在输入框中输入网址，点击按钮发送请求。
 * 然后会在标准输出中产生相应的结果。
 * */
#include <QApplication>
#include "myCallback.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MyCallback my;
	my.show();
	return app.exec();
}
