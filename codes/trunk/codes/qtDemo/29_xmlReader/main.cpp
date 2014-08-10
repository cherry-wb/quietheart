/*程序演示了如何读取xml文件中的内容
 * 读取xml文件，使用xmlstreamreader
 * 写xml文件省略了，应该使用xmlstreamwriter,参见messdemo
 * 例子xml文件是simpleXml
 * 点击窗口就会读取一下，然后输出到标准输出。
 * 需要对xml有所了解，即：
 * 1）每个元素有一个开始标记<元素名>和结束标记</元素名>
 * 2)在开始标记中还可以添加元素的一些特殊属性
 * 3）开始标记和结束标记之间可以有任意的字符串和其他的子元素。
 * 关键注意，处理xml相关的类使用的是#include <QtCore/类名>而不是直接类名了
 * */
#include<QApplication>
#include "myCallback.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MyCallback my;
	my.show();
	return app.exec();
}
