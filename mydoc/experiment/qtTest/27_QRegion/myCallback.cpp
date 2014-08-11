#include "myCallback.h"
#include <iostream>
MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	;
}

void MyCallback::callback(void)
{
	using std::cout;
	using std::endl;
	cout<<"called callback!"<<endl;
}
