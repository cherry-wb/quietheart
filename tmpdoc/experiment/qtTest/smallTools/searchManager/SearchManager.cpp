#include "SearchManager.h"

#include <QCheckBox>
#include <QComboBox>
#include <QStringList>
#include <QtDebug>


SearchManager::SearchManager(QWidget *parent):QWidget(parent)
{
	/*
	checkBooks = NULL;
	checkDocuments = NULL;
	checkPhotos = NULL;
	checkMusic = NULL;
	checkWikipedia = NULL;
	wikiCombo= NULL;
	*/
	init();
	updateLayout();
}

void SearchManager::init()
{
	//check options
	optionTexts<<"    Books"<<"    Documents"<<"    Photos"<<"    Music"<<"    Wikipedia";
	for(int i = 0; i < optionTexts.count(); ++i)
	{
		checkOptions<<(new QCheckBox(optionTexts[i], this));
		//checkOptions[i]->setObjectName("E"+optionText[i]);
		connect(checkOptions[i],SIGNAL(stateChanged(int)),this,SLOT(stateChanged(int)));
	}

	//combo box
	wikiCombo= new QComboBox(this);
	wikiCombo->addItem(QString("English"));
	wikiCombo->addItem(QString("Chinese"));
	wikiCombo->addItem(QString("Japanese"));
	connect(wikiCombo,SIGNAL(activated(const QString&)),this,SLOT(actived(const QString&)));
}

void SearchManager::updateLayout()
{
	setFixedWidth(ESEARCHWIDTH);
	setFixedHeight(ESEARCHHEIGHT);
	for(int i = 0; i < checkOptions.count(); ++i)
	{
		checkOptions[i]->setGeometry(width()/8,i*height()/checkOptions.count(),
									width()/3, ESEARCHITEMHEIGHT);

	}
	wikiCombo->setGeometry(checkOptions.last()->geometry().topRight().x(),
						checkOptions.last()->geometry().topRight().y(), 
						checkOptions.last()->width(),checkOptions.last()->height());
}

void SearchManager::stateChanged(int state)
{
	//get object who send signal
	QCheckBox *check = qobject_cast<QCheckBox *>(sender());
	qDebug()<<"checkbox text is:"<<check->text();
	qDebug()<<"the state of checkbox is changed to"<<state;
	if(check->text() == "Books")
	{
		qDebug()<<"selected Books";
	}
	else if(check->text().endsWith("Documents"))
	{
		qDebug()<<"selected Documents";
	}
	else if(check->text().endsWith("Photos"))
	{
		qDebug()<<"selected Photos";
	}
	else if(check->text().endsWith("Music"))
	{
		qDebug()<<"selected Music";
	}
	else if(check->text().endsWith("Wikipedia"))
	{
		qDebug()<<"selected Wikipedia";
	}
	else
	{
		qDebug()<<"unknown check!";
	}
}

void SearchManager::actived(const QString &text)
{
	qDebug()<<"The actived text is:"<<text;
}
