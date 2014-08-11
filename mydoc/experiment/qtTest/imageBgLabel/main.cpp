/*给一个label设置其背景图片，然后再给label设置上面的文字，不会覆盖背景图片。
 * */
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QString>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QWidget window;
	QVBoxLayout *vbox = new QVBoxLayout();

	QString iconPath = "./load.png";
	QPixmap pix1 = QPixmap(iconPath);
	pix1.scaled(200,60);
	QPixmap pix2 = QPixmap(iconPath);

	QLabel *label1 = new QLabel("");
	//label1->setPixmap(pix1);
	label1->setStyleSheet("* { background-image: url(./load.png);background-position: top left;background-origin: content;}");
	label1->setText("test1");

	QLabel *label2 = new QLabel("");
	QString text2("test2");
	QPainter paintP1;
	paintP1.begin(&pix2); 
	paintP1.drawText(pix2.width()>>1,pix2.height()>>1,text2);
	paintP1.end();
	label2->setPixmap(pix2);

	vbox->addWidget(label1);
	vbox->addWidget(label2);
	window.setLayout(vbox);
	window.show();
	return app.exec();
}
