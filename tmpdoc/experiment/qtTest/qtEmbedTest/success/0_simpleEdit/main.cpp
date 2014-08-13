#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	app.setFont(QFont("wenquanyi", 10));
	//app.setDefaultCodec(QTextCodec::codecForName("UTF-8"));
	QWidget window;

	QHBoxLayout* layout = new QHBoxLayout;

	QLabel* label = new QLabel;
	label->setText("input:");
	layout->addWidget(label);

	QLineEdit *le = new QLineEdit;
	layout->addWidget(le);

	QPushButton* btn = new QPushButton("&Quit");
	QObject::connect(btn, SIGNAL(clicked()), qApp, SLOT(quit()));
	layout->addWidget(btn);

	window.setLayout(layout);
	
	//以最大化的形式显示窗口
	window.showMaximized();
	//window.show();
	return app.exec();
}
