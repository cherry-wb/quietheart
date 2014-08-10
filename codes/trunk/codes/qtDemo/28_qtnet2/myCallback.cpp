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
	lineUrl->setText("http://192.168.0.118/mediawiki/index.php?action=view&title=mytest1");
	lineUrl->setReadOnly(true);

	QPushButton *btn = new QPushButton("send",this);
	connect(btn, SIGNAL(clicked()), this, SLOT(clicked()));

	lineUrl->setGeometry(0,20,width()/3*2,60);
	btn->setGeometry(width()/3*2,20,width()/3,60);

}
void MyCallback::clicked()
{
	QNetworkRequest request;
	lineUrl->setText("http://192.168.0.118/mediawiki/index.php?action=view&title=mytest1");
	//发送php请求
	//效果相当于在浏览器输入:
	//http://192.168.0.118/mediawiki/index.php?action=view&title=mytest1
	QByteArray content = "title=mytest1";
	int contentLength = content.length();
	QNetworkRequest req;
	req.setUrl(QUrl("http://192.168.0.118/mediawiki/index.php?action=view"));
	req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
	req.setHeader(QNetworkRequest::ContentLengthHeader,contentLength);
	QNetworkReply *rtn = manager->post(req,content);
	qDebug()<<"send pointer:"<<(int)rtn;//get请求，会和finished的参数地址一样。
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
