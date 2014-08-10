/*功能:
 * 测试设置父窗口中自窗口的叠放次序;以及在qlabel中简单添加一个纯色pixmap;
 */
#include <QApplication>
#include <QWidget>
#include <QLabel>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QWidget window;
	window.resize(200,200);

	//label1
	QLabel *label1 = new QLabel(&window);
	QPixmap pm1(100,100);
	pm1.fill(QColor(255,0,0));
	label1->setPixmap(pm1);
	label1->setFixedSize(100,100);

	//label2
	QLabel *label2 = new QLabel(&window);
	QPixmap pm2(100,100);
	pm2.fill(QColor(0,0,255));
	label2->setPixmap(pm2);
	label2->setFixedSize(100,100);

	label2->move(0,0);
	label1->move(0,0);
	//这时候，label1被label2挡住了。

	label1->raise();//将label1从父窗口的栈中提升,这样label1就挡住label2了
	window.show();
	return app.exec();
}
