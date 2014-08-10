/*程序功能：测试QSplitter
 * QSplitter是一个可以添加其他控件的容器，多个容器之间有一个split边界可以拖拽.
 * 默认是水平方向的添加。
 * 发现一个问题，如果不用new分配的话，退出程序的时候会有许多的警告信息,原因是先构造的后释放。
 * btn是子窗口，先构造了btn，导致先释放其父窗口，后释放btn所有有问题了。这时候需要改变一下次序，让btn在 splitter之后调用。
 * */
#include <QApplication>
#include <QPushButton>
#include <QSplitter>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QPushButton *btn1 = new QPushButton("test1");
	QPushButton *btn2 = new QPushButton("test2");
	QPushButton *btn3 = new QPushButton("test3");

	QSplitter *splitter = new QSplitter(0);
	splitter->setOrientation(Qt::Vertical);
	splitter->addWidget(btn1);
	splitter->addWidget(btn2);
	splitter->addWidget(btn3);

	splitter->show();
	int status = app.exec();
	delete splitter;
	return status;
}
