#include"myUIWidget.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MyWidget widget;
	widget.show();
	app.exec();
	return 0;
}
