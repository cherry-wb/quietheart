#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPainter>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QWidget window;
	QImage img1("qtlogo.png");

	QPainter *painter = new QPainter(&window);
	painter->drawImage(80, 64, img1);
	window.show();

	return app.exec();
}
