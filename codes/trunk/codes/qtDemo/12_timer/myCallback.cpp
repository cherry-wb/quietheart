#include "myCallback.h"
#include <iostream>
MyCallback::MyCallback(QObject *parent):QObject(parent)
{
	;
}

void MyCallback::callback(void)
{
	using std::cout;
	using std::endl;
	cout<<"timer out!"<<endl;
}
