/*程序功能：
 * 一个简单的Qt网络编程的例子
 * 注意：
 * 1)编译的时候需要在.pro文件中加入：LIBS+=-lQtWebKit
 * 2)包含头文件的时候需要加上前缀QtNetwork
 *	#include <QtNetwork/QNetworkAccessManager>
 * 否则无法编译
 * 程序功能是：
 * 有一个输入框(只读)和一个按钮。点击按钮发送php请求,请求的效果相当于输入框中显示的。
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
