#include<QApplication>
#include <iostream>
using std::cout;
using std::endl;
int flag = 4;
int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	++flag;
	cout<<flag<<endl;
	return app.exec();
}
