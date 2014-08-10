/* 程序功能：窗口内有一个formLayout
 *formlayout的功能是添加每行两列的控件，两列分别是标签和一个QWidget
 * */
#include <QApplication>
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	QWidget window;
	window.resize(320, 240);

	QLineEdit *lineEdit1 = new QLineEdit;
	QLineEdit *lineEdit2 = new QLineEdit;

	//formlayout
	QFormLayout *flayout = new QFormLayout;
	flayout->addRow(QObject::tr("&Name:"), lineEdit1);
	flayout->addRow(QObject::tr("&Email:"), lineEdit2);

	window.setLayout(flayout);
	window.show();
	return a.exec();
}

