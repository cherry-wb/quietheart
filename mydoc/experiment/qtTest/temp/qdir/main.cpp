#include <QApplication>
#include <QDir>
int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	QDir dir("/mnt/myOwn_all/experiment/program/qtTest/temp/qdir");
	dir.remove("test");
	return 0;
}
