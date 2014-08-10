#include "myCallback.h"
#include <QGridLayout>
#include <QAction>
#include <QStringList>
#include <QMenu>
#include <QtDebug>


EComboLabel::EComboLabel(QWidget *parent):QWidget(parent)
{
	init();
}

void EComboLabel::init()
{
	selectMenu = NULL;
	QGridLayout *gl = new QGridLayout();
	setLayout(gl);

	titleLabel = new EPushLabel("None");
	arrowLabel = new EPushLabel("V");

	gl->addWidget(titleLabel,0,0,1,4);
	gl->addWidget(arrowLabel,0,4,1,1);

	//default action here for test, should be removed.
	addItem(QString("English"));
	addItem(QString("Chinese"));
	addItem(QString("Japanese"));

	connect(titleLabel,SIGNAL(pressSignal()), this, SLOT(clicked()));
	connect(arrowLabel,SIGNAL(pressSignal()), this, SLOT(clicked()));

}

void EComboLabel::updateLayout()
{
	qDebug()<<"nothing";
}
void EComboLabel::addItem(QString title)
{
	if(selectMenu == NULL)
	{
		selectMenu = new QMenu(this);
	}
	itemTitles<<title;
	selectItems<<new QAction(title,selectMenu);
	connect(selectItems.last(), SIGNAL(triggered()),this,SLOT(activeItem()));
	selectMenu->addAction(selectItems.last());
}

void EComboLabel::activeItem()
{
	QAction *action = qobject_cast<QAction*>(sender());
	qDebug()<<"selected the :"<<action->text();
	titleLabel->setText(action->text());
	emit activated(action->text());
}
void EComboLabel::clicked()
{
	qDebug()<<"clicked the label!";
	if(selectMenu)
	{
		QRect menuRect;
		//menuRect.setBottom(titleLabel->geometry().bottom());
		//menuRect.setBottom(0);
		//menuRect.setWidth(geometry().width());
		//selectMenu->setGeometry(menuRect);
		selectMenu->move(geometry().x(), geometry().y()-selectMenu->height());
		selectMenu->setFixedWidth(titleLabel->width());
		selectMenu->exec();
	}
}
