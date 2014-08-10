/*程序功能：
 * 对QSignalMapper类的使用。
 * 这个类可以把一个无参数的信号如clicked()绑定到一个QSignalMapper的map()槽上，
 * 然后由QSignalMapper来产生字符串或者整数等消息。
 * 即"发送者构件signal-->QSignalMapper的map槽(该槽发送信号mapped),
 * QsignalMapper的mapped信号--->接收者构件slot"
 * 本程序实现了：
 * 点击一个按钮，发送一个字符串消息。
 * 点击一个按钮，发送一个整数消息。
 * */
#include <QApplication>
#include "myCallback.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MyCallback my;
	my.show();
	app.exec();
	return 0;
}
