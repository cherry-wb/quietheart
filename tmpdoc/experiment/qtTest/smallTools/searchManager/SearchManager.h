#ifndef __SEARCHMANAGER_H
#define __SEARCHMANAGER_H
#include <QWidget>
#include <QList>

#define ESEARCHWIDTH 600
#define ESEARCHHEIGHT 800
#define ESEARCHITEMHEIGHT 60
class QComboBox;
class QCheckBox;
class QStringList;
class SearchManager:public QWidget
{
	Q_OBJECT
	public:
		SearchManager(QWidget *parent = 0);
	protected:
		//void timerEvent(QTimerEvent *event);
	private:
		void init();
		void updateLayout();
	protected slots:
		void stateChanged(int);
		void actived(const QString&);
	private:
	/*
	QCheckBox *checkBooks;
	QCheckBox *checkDocuments;
	QCheckBox *checkPhotos;
	QCheckBox *checkMusic;
	QCheckBox *checkWikipedia;
	*/
	QList<QCheckBox*> checkOptions;
	QStringList optionTexts;
	QComboBox *wikiCombo;
};
#endif
