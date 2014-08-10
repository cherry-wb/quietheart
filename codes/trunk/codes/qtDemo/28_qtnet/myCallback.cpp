#include "myCallback.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QPushButton>
#include <QLineEdit>
#include <QtDebug>


MyCallback::MyCallback(QWidget *parent):QWidget(parent)
{
	manager = new QNetworkAccessManager(this);
	QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(finished(QNetworkReply*)));//HTTP请求已完成

	lineUrl = new QLineEdit(this);
	lineUrl->setText("http://");

	QPushButton *btn = new QPushButton("send",this);
	connect(btn, SIGNAL(clicked()), this, SLOT(clicked()));

	lineUrl->setGeometry(0,20,width()/3*2,60);
	btn->setGeometry(width()/3*2,20,width()/3,60);

}
void MyCallback::clicked()
{
	QNetworkRequest request;
	//request.setUrl(QUrl("http://192.168.0.118/index.html"));
	request.setUrl(QUrl(lineUrl->text()));
	QNetworkReply *reply = manager->get(request);
	//lineUrl->setText("http://");
	qDebug()<<"send pointer:"<<(int)reply;//get请求，会和finished的参数地址一样。
}

void MyCallback::finished(QNetworkReply* reply)
{
	qDebug()<<"@@@@@@{"<<__PRETTY_FUNCTION__;
	qDebug()<<"receive pointer:"<<(int)reply;//和发get请求的指针是同一个地址。
	qDebug()<<reply->readBufferSize()<<"==========";

	//获取reply的属性
	QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

	// "200 OK" received?
	qDebug()<<statusCodeV.toInt();
	if (statusCodeV.toInt()==200)
	{
		//TODO: read data from QNetworkReply
		//Example of creating QImage from the reply
		//QImageReader imageReader(reply);
		//QImage pic = imageReader.read();

		//Example of reading bytes form the reply
		QByteArray bytes = reply->readAll();  // bytes
		//QString string(bytes); // string
		QString string = QString::fromUtf8(bytes.data());
		qDebug()<<"The received data:"<<string;//返回的是网页的内容，默认index
	}
	// Some http error or redirect
	else
	{
		// TODO: 
		qDebug()<<"some error or redirect";
	}

	delete reply;
	qDebug()<<"@@@@@@}"<<__PRETTY_FUNCTION__;
}
