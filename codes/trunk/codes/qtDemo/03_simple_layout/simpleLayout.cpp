/* 程序功能：窗口内有一个lable并排一个输入框，下面还有一个按钮。
 * */
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	QWidget window;
	window.resize(320, 240);
	window.show();

	//label&lineEdit
	//因为它们添加到layout上面，所以用指针来new会自动释放的，如果不用指针会警告
	//tr是多语言支持,但仍不能中文?
	QLabel *label = new QLabel(QObject::tr("Name:"));
	QLineEdit *lineEdit = new QLineEdit;

	//hlayout
	QHBoxLayout *hlayout = new QHBoxLayout;
	hlayout->addWidget(label);
	hlayout->addWidget(lineEdit);

	//button
	//&在字母前面是快捷键alt+Q
	QPushButton *button = new QPushButton( "&Quit!");
	//这里点击设置按钮则关闭程序
	QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()));
	//button.show();//显示按钮

	//vlayout
	QVBoxLayout vlayout;
	//QVBoxLayout vlayout(&window);//如果用这个初始化那么后面也不用window.setLayout了
	vlayout.addLayout(hlayout);
	vlayout.addWidget(button);

	window.setLayout(&vlayout);//这里设置选用哪个布局
	return a.exec();
}

