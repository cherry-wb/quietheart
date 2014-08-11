//for dependency
#include "platforminterface.h"
#include "qabstractbrowserscreen.h"
#include "qtopiaserverapplication.h"
#include "qabstractheader.h"
#include "qabstractcontextlabel.h"
#include "windowmanagement.h"
#include "launcherview.h"
//for use
#include <QDesktopWidget>
#include <QSoftMenuBar>
#include <QMenu>
#include <QAction>
#include <QColor>
#include <QPainter>
#include <QFont>
#include <QStackedWidget>
#include <QSignalMapper>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QContent>
#include <QDataStream>
#include <QByteArray>
#include <QtopiaChannel>
#include <QIODevice>
#include <QBuffer>
#include <QProcess>
#include <iostream>

//for debug
#include <QDebug>
#include <assert.h>

PlatformServerInterface::PlatformServerInterface(QWidget* parent, Qt::WFlags flags)
    : QAbstractServerInterface(parent, flags)
    , m_header(0)
    , m_desktop(0)
    , m_context(0)
    , searchLine(0)
    , searchWindow(0)
    , m_setting_list(0)
    , m_setting_container(0)
    , m_stack(new QStackedWidget(this))
{
	qDebug()<<__PRETTY_FUNCTION__;

	// init desktop
	initDesktop();

	// init title bar
	m_header = qtopiaWidget<QAbstractHeader>();
	Q_ASSERT_X(m_header, "Platform Desktop", "QAbstractHeader not available");
	WindowManagement::protectWindow(m_header);

	// init context bar
	m_context = qtopiaWidget<QAbstractContextLabel>();
	Q_ASSERT_X(m_header, "Platform Desktop", "QAbstractContextLabel not available");
	WindowManagement::protectWindow(m_context);

	// layout header and context bars
	QSize titleSize = m_header ? m_header->reservedSize() : QSize(0,0);
	WindowManagement::dockWindow(m_header, WindowManagement::Top, titleSize);
	m_header->show();
	QSize contextSize = m_context ? m_context->reservedSize() : QSize(0,0);
	WindowManagement::dockWindow(m_context, WindowManagement::Bottom, contextSize);
	m_context->show();

	// documents view
	LauncherView *lv = LauncherView::createLauncherView("DocumentLauncherView", this, 0);
	QObject::connect(lv, SIGNAL(clicked(QContent)),
			this, SLOT(execContent(QContent)));              
	m_stack->addWidget(lv);

	// setting menus(move to initDesktop?)
	if(m_setting_list == 0)
	{
		m_setting_container = new QWidget(m_stack);
		m_setting_list = new QListWidget(m_setting_container);
		m_setting_list->setGeometry(0,60,600,800);//to be improved
		m_setting_list->setStyleSheet("background-color: white;");//to be improved
		m_setting_list->setSelectionMode(QAbstractItemView::SingleSelection);
		QObject::connect(m_setting_list, SIGNAL(itemClicked(QListWidgetItem*)),
				this, SLOT(onSettingList(QListWidgetItem*)));

		QListWidgetItem *dateTime = new QListWidgetItem;
		dateTime->setText(tr("Date and Time"));
		m_setting_list->addItem(dateTime);
		dateTime->setSizeHint(QSize(580, 50));//to be improved 

		QListWidgetItem *nextPage = new QListWidgetItem;
		nextPage->setText(tr("Next Page Defination"));
		m_setting_list->addItem(nextPage);
		nextPage->setSizeHint(QSize(580, 50));//to be improved 

		QListWidgetItem *eng = new QListWidgetItem;
		eng->setText(tr("English"));
		m_setting_list->addItem(eng);
		eng->setSizeHint(QSize(580, 50));//to be improved 

		QListWidgetItem *fanti = new QListWidgetItem;
		fanti->setText(QString::fromUtf8("繁體中文"));
		m_setting_list->addItem(fanti);
		fanti->setSizeHint(QSize(580, 50));//to be improved 

		QListWidgetItem *jianti = new QListWidgetItem;
		jianti->setText(QString::fromUtf8("简体中文"));
		m_setting_list->addItem(jianti);
		jianti->setSizeHint(QSize(580, 50));//to be improved 

		QListWidgetItem *jpn = new QListWidgetItem;
		jpn->setText(QString::fromUtf8("日本語"));
		m_setting_list->addItem(jpn);
		jpn->setSizeHint(QSize(580, 50));//to be improved 

		QListWidgetItem *shutDown = new QListWidgetItem;
		shutDown->setText(tr("Device Shut Down"));
		m_setting_list->addItem(shutDown);
		shutDown->setSizeHint(QSize(580, 50));//to be improved 

		QListWidgetItem *screenSaver = new QListWidgetItem;
		screenSaver->setText(tr("Screen Saver"));
		m_setting_list->addItem(screenSaver);
		screenSaver->setSizeHint(QSize(580, 50));//to be improved 

		QListWidgetItem *restore = new QListWidgetItem;
		restore->setText(tr("Restore Defaults"));
		m_setting_list->addItem(restore);
		restore->setSizeHint(QSize(580, 50));//to be improved 

		QListWidgetItem *about = new QListWidgetItem;
		about->setText(tr("About"));
		m_setting_list->addItem(about);
		about->setSizeHint(QSize(580, 50));//to be improved 
	}
	m_stack->addWidget(m_setting_container);

	// show desktop widget.
	if(m_desktop)
	{
		m_stack->setCurrentWidget(m_desktop);
		setFocusProxy(m_desktop);
		m_desktop->setFocus();
	}
}

PlatformServerInterface::~PlatformServerInterface(){}

void PlatformServerInterface::initDesktop()
{
	//stack is the main container
	QDesktopWidget *desktop = QApplication::desktop();
	QRect desktopRect = desktop->screenGeometry(desktop->primaryScreen());
	setGeometry(desktopRect);
	m_stack->setGeometry(0,0,desktopRect.width(),desktopRect.height());//to be improved

	//create desktop in the stack
	m_desktop = new QWidget(m_stack);
	m_desktop->setGeometry(rect());
	qDebug()<<"qpe desktop geometry ="<<m_desktop->geometry();
	m_stack->addWidget(m_desktop);

#if 1 //XXX : useless now, to be removed.
	if(QFile::exists("/tmp/.qpewhite"))
	{
		qDebug()<<__PRETTY_FUNCTION__<<"force to paint white background.";
		QLabel *bgLabel = new QLabel(m_desktop);
		QPixmap bgpix(600,800);
		QPainter painter(&bgpix);
		painter.fillRect(QRect(0,0,600,800), QColor(255,255,255));
		bgLabel->setPixmap(bgpix);
		bgLabel->setGeometry(0,0,600,800);
	}
#endif

	// create and init buttons
	createButtons();

	// build up soft menu for desktop
	QMenu *softMenu = QSoftMenuBar::menuFor(m_desktop);
	softMenu->setFont(QFont("Times",10,QFont::Bold));

	QSignalMapper* mapper = new QSignalMapper(this);
	connect(mapper, SIGNAL(mapped(const QString&)),
		this, SLOT(actionClicked(const QString&)));

	QAction *actionBookstore = new QAction(QIcon(":icon/start"),
						tr("Bookstore"), m_desktop);
	mapper->setMapping(actionBookstore, "Bookstore");
	connect(actionBookstore, SIGNAL(triggered()),
		mapper, SLOT(map()));
	softMenu->addAction(actionBookstore);
	//softMenu->addSeparator();

	QAction *actionDictionary = new QAction(QIcon(":icon/start"),
						tr("Dictionary"), m_desktop);
	mapper->setMapping(actionDictionary, "Dictionary");
	connect(actionDictionary, SIGNAL(triggered()),
		mapper, SLOT(map()));
	softMenu->addAction(actionDictionary);
	//softMenu->addSeparator();

	QAction *actionPhotos = new QAction(QIcon(":icon/start"),
					tr("Photos"), m_desktop);
	mapper->setMapping(actionPhotos, "Photos");
	connect(actionPhotos, SIGNAL(triggered()),
		mapper, SLOT(map()));
	softMenu->addAction(actionPhotos);
	//softMenu->addSeparator();

	QAction *actionSearch = new QAction(QIcon(":icon/start"),
					tr("Search"), m_desktop);
	mapper->setMapping(actionSearch, "Search");
	connect(actionSearch, SIGNAL(triggered()),
		mapper, SLOT(map()));
	softMenu->addAction(actionSearch);
	softMenu->addSeparator();

	QAction *actionSettings = new QAction(QIcon(":icon/start"),
					tr("Settings"), m_desktop);
	mapper->setMapping(actionSettings, "Settings");
	connect(actionSettings, SIGNAL(triggered()),
		mapper, SLOT(map()));
	softMenu->addAction(actionSettings);
	softMenu->addSeparator();


	// build up widgets for "Search" in soft menu bar
	int width = desktop->screenGeometry(0).size().width();
	int height = desktop->screenGeometry(0).size().height();

	searchWindow = new QWidget;
	searchWindow->setStyleSheet("background-color: white;");//to be improved
	QVBoxLayout *searchVlayout = new QVBoxLayout;
	searchVlayout->setMargin(width / 10);

	QGridLayout *searchGridlayout = new QGridLayout;
	searchGridlayout->setMargin(0);
	searchGridlayout->setHorizontalSpacing(width / 10);
	searchGridlayout->setVerticalSpacing(height / 20);

	QPushButton *btnSearchBookitems = new QPushButton(tr("Search book items"));
	btnSearchBookitems->setStyleSheet("background-color: white;"
			"selection-color: white;"
			"border-width: 2px;"
			"border-radius: 8px;"
			"border-style: solid;"
			"border-color: grey;"
			"color: black;");//to be improved
	searchGridlayout->addWidget(btnSearchBookitems, 0, 0);
	btnSearchBookitems->setFocusPolicy(Qt::NoFocus);	

	QPushButton *btnSearchDocument = new QPushButton(tr("Search document"));
	btnSearchDocument->setStyleSheet("background-color: white;"
			"selection-color: white;"
			"border-width: 2px;"
			"border-radius: 8px;"
			"border-style: solid;"
			"border-color: grey;"
			"color: black;");//to be improved
	searchGridlayout->addWidget(btnSearchDocument, 0, 1);
	btnSearchDocument->setFocusPolicy(Qt::NoFocus);	

	QPushButton *btnSearchWiki = new QPushButton(tr("Search wikipedia"));
	btnSearchWiki->setStyleSheet("background-color: white;"
			"selection-color: white;"
			"border-width: 2px;"
			"border-radius: 8px;"
			"border-style: solid;"
			"border-color: grey;"
			"color: black;");//to be improved
	searchGridlayout->addWidget(btnSearchWiki, 1, 0);
	btnSearchWiki->setFocusPolicy(Qt::NoFocus);	

	QPushButton *btnSearchMp3 = new QPushButton(tr("Search mp3"));
	btnSearchMp3->setStyleSheet("background-color: white;"
			"selection-color: white;"
			"border-width: 2px;"
			"border-radius: 8px;"
			"border-style: solid;"
			"border-color: grey;"
			"color: black;");//to be improved
	searchGridlayout->addWidget(btnSearchMp3, 1, 1);
	btnSearchMp3->setFocusPolicy(Qt::NoFocus);	


	searchLine = new QLineEdit;
	searchLine->setStyleSheet("background-color:white;"
			"border-bottom-style:solid;"
			"border-top-style:flat;"
			"border-left-style:flat;"
			"border-right-style:flat;"
			"border-width:2px;"
			"border-radius:2px;"
			"border-bottom-color:grey;");//to be improved

	QPushButton *btnSearchBottom = new QPushButton(tr("Search"));
	btnSearchBottom->setStyleSheet("background-color: #a3a3a3;"
			"selection-color: white;"
			"border-width: 2px;"
			"border-radius: 8px;"
			"border-style: solid;"
			"border-color: grey;"
			"color: black;");//to be improved
	btnSearchBottom->setFixedWidth(130);//to be improved
	QHBoxLayout *searchHlayout = new QHBoxLayout;
	searchHlayout->addWidget(btnSearchBottom);
	btnSearchBottom->setFocusPolicy(Qt::NoFocus);	

	searchVlayout->addLayout(searchGridlayout);
	searchVlayout->addWidget(searchLine);
	searchVlayout->addLayout(searchHlayout);
	searchWindow->setLayout(searchVlayout);

	QObject::connect(btnSearchDocument, SIGNAL(clicked()),
			this, SLOT(OnDocumentSearchClicked()));
	QObject::connect(btnSearchMp3, SIGNAL(clicked()),
			this, SLOT(OnMp3SearchClicked()));


	// see if we need a focus proxy.
	// this is used to avoid whole-area update when the menu shows or hides.
	QWidget * focusproxy = m_desktop;
#if 1
	QSettings tmpcfg("Trolltech","qpe");
	bool needproxy = tmpcfg.value("zhaohp/update_menu_area_only",false).toBool();
	if(needproxy)
	{
		qDebug()<<__PRETTY_FUNCTION__<<"desktop needs a focus proxy!";
		focusproxy = new QWidget(m_desktop);
		focusproxy->setFixedSize(0,0);
		focusproxy->setGeometry(600,800,0,0);
		m_desktop->setFocusProxy(focusproxy);
	}
#endif

	// change context bar labels(or softmenu bar labels).
	// these must happen after QSoftMenuBar::menuFor(),
	// otherwise the labels will be reset to standard ones.
	QSoftMenuBar::setLabel( focusproxy, QSoftMenuBar::keys().at(0),
				":icon/options", "More", QSoftMenuBar::AnyFocus );
	QSoftMenuBar::setLabel( focusproxy, QSoftMenuBar::keys().at(1),
				QSoftMenuBar::NoLabel, QSoftMenuBar::AnyFocus);
	QSoftMenuBar::setLabel( focusproxy, QSoftMenuBar::keys().at(2),
				QSoftMenuBar::NoLabel, QSoftMenuBar::AnyFocus);

	QSoftMenuBar::setLabel( softMenu, QSoftMenuBar::keys().at(0),
				":icon/options", "More", QSoftMenuBar::AnyFocus );
	QSoftMenuBar::setLabel( softMenu, QSoftMenuBar::keys().at(1),
				QSoftMenuBar::NoLabel, QSoftMenuBar::AnyFocus);
	QSoftMenuBar::setLabel( softMenu, QSoftMenuBar::keys().at(2),
				QSoftMenuBar::NoLabel, QSoftMenuBar::AnyFocus);

	QSoftMenuBar::setHelpEnabled(m_desktop, false);
}

void PlatformServerInterface::createButtons()
{
	//create default .conf file.
	QSettings test(QSettings::SystemScope, "Trolltech","HomeDesktop");
	if(!QFile::exists(test.fileName())) {
		defaultButtons();
	}

	//create buttons according to the .conf file.
	QSettings settings(QSettings::SystemScope, "Trolltech","HomeDesktop");
	int numbtns = settings.childGroups().size();
	// all the groups are buttonN, N is a number start from 0.
	for(int i=0; i<numbtns; i++)
	{
		// read from setting file, group `buttonN`
		QString gpname = QString("button%1").arg(i);
		settings.beginGroup(gpname);
		QString entry = settings.value("entry").toString();
		QString args = settings.value("exeargs").toString();
		QString icon = settings.value("icon").toString();
		QString title = settings.value("title").toString();
		QString text = settings.value("text").toString();

		int titlefontsize = settings.value("titlefontsize",7).toInt();
		int textfontsize = settings.value("textfontsize",6).toInt();

		bool okLeft,okTop,okWidth,okHeight;
		okLeft = okTop = okWidth = okHeight = false;
		int left = settings.value("left").toInt(&okLeft);
		int top = settings.value("top").toInt(&okTop);
		int width = settings.value("width").toInt(&okWidth);
		int height = settings.value("height").toInt(&okHeight);
		settings.endGroup();
		// read setting file done.

		// do some assert jobs.
		Q_ASSERT_X((okLeft && okTop), "Platform Desktop",
			"Error in HomeDesktop.conf, check `left` and `top`!");
		Q_ASSERT_X(!icon.isEmpty(), "Platform Desktop",
			"Error in HomeDesktop.conf, `icon` must not be empty!");
		if(entry.isEmpty())
		{qWarning()<<"Platform Desktop :"<<gpname<<"entry is empty!";}

		// process some result values.
		icon = Qtopia::qtopiaDir() + icon;
		if(entry.startsWith("Applications"))
		{ entry = Qtopia::qtopiaDir() + "apps/" + entry; }
		QFont titleFont("Times", titlefontsize, QFont::Bold);
		QFont textFont("Times", textfontsize, QFont::Normal);

		text = gpname;

		// create a HomeButton.
		HomeButton *btn = new HomeButton(m_desktop);
		m_btnList.append(btn);
		btn->setIcon(icon);
		btn->setTitle(title, &titleFont);
		btn->setText(text, &textFont);
		btn->setEntry(entry, args.split(" "));
		btn->setGeometry(left, top, btn->width(), btn->height());
		QObject::connect(btn, SIGNAL(clicked(QString,QStringList)), 
				this, SLOT(launchApp(QString,QStringList)));

		// if width and height are set, respect the settings, 
		// but we won't resize the icon or other things. 
		// this is not important, and might not support next version.
		if(okWidth){btn->setFixedWidth(width);}
		if(okHeight){btn->setFixedHeight(height);}
	}

	//fix tip text for the buttons.
	//ContinueReading:
	QSettings *crcfg = new QSettings(QSettings::SystemScope, "Trolltech", "continueReading.conf");
	QString continueName(crcfg->value("Name", "N/A").toString());
	m_btnList.at(0)->setText( continueName );

	//Books:
	QDir *booksDir = new QDir(Qtopia::documentDir());
	booksDir->setNameFilters(QStringList()<<"*.epub");
	int booksNum = booksDir->count();
	m_btnList.at(1)->setText( QString("%1 books").arg(booksNum) );
	//qDebug()<<booksDir->entryList();

	//Music:
	QDir *musicDir = new QDir(Qtopia::documentDir());
	musicDir->setNameFilters(QStringList()<<"*.wma"<<"*.mp3"<<"*.wav");
	int musicNum = musicDir->count();
	m_btnList.at(2)->setText( QString("%1 musics").arg(musicNum) );
	//qDebug()<<musicDir->entryList();

	//Documents:
	QDir *docDir = new QDir(Qtopia::documentDir());
	docDir->setFilter(QDir::AllDirs|QDir::NoDotAndDotDot);
	int dirNum = docDir->count();
	m_btnList.at(3)->setText( QString("%1 folders").arg(dirNum) );
	//qDebug()<<docDir->entryList();

	//Sketch:
	QDir *notesDir = new QDir(Qtopia::documentDir()+"Sketch/");
	notesDir->setFilter(QDir::Files);
	int msgNum = notesDir->count();
	m_btnList.at(4)->setText( QString("%1 messages").arg(msgNum) );
	//qDebug()<<notesDir->entryList();
}

void PlatformServerInterface::showEvent(QShowEvent *)
{
    if(m_header && !m_header->isVisible()) {
        m_header->raise();
        m_header->show();
    }
    if (m_context && !m_context->isVisible()) {
        m_context->raise();
        m_context->show();
    }
}

void PlatformServerInterface::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == QSoftMenuBar::keys().at(2))
    {//back key.
        qDebug()<<"PlatformServerInterface::keyPressEvent -"<<"back key pressed.";
        if(m_stack->currentIndex() == 1) // back from docunents view.
        {
            m_stack->setCurrentIndex(0); // return to desktop.
            window()->setWindowTitle("");
        }
        else if(m_stack->currentIndex() == 2) // back from setting view.
        {
            m_stack->setCurrentIndex(0); // return to desktop.
            window()->setWindowTitle("");
        }
    }
}

void PlatformServerInterface::execContent(const QContent & content)
{
    qDebug()<<__PRETTY_FUNCTION__<<content;
    content.execute();
}

void PlatformServerInterface::launchApp(const QString & entry, const QStringList & args)
{
    if(entry.endsWith(".desktop"))
    {
        QContent applink(entry,false);
        qDebug()<<"Launch application"<<entry;
        qDebug()<<applink<<args;
        applink.execute();
    }
    else if(entry == "Documents")
    {
        qDebug()<<"open"<<entry;
        m_stack->setCurrentIndex(1);
        window()->setWindowTitle("Documents");
    }
    else
    {
        qDebug()<<"Launch application"<<entry;
        QProcess::startDetached(entry);
    }
}
void PlatformServerInterface::actionClicked(const QString &act)
{
    if(act == "Bookstore")
    {
	    qDebug()<<"Bookstore clicked";
    }
    else if(act == "Dictionary")
    {
	    qDebug()<<"Dictionary clicked";
	    QString path;
	    //path = Qtopia::qtopiaDir() + "bin/StartDic.sh";
	    system("/usr/local/qtex/bin/StartDic.sh");
    }
    else if(act == "Photos")
    {
	    qDebug()<<"Photos clicked";
	    system("/usr/local/qtex/bin/photoedit&");
    }
    else if(act == "Search")
    {
	    qDebug()<<"Search clicked";
	    showSearchFrame();
    }
    else if(act == "Settings")
    {
	    qDebug()<<"Settings clicked";
	    m_stack->setCurrentIndex(2);
    }
    else
    {
	    qDebug()<<"Action clicked";
    }
}
void PlatformServerInterface::onSettingList(QListWidgetItem *item)
{
    QString text(item->text());
    if(text == tr("Date and Time"))
    {
	    qDebug()<<text;
	    system("/usr/local/qtex/bin/systemtime&");
	 return;
    }
    else if(text == tr("Next Page Defination"))
    {
	    qDebug()<<text;
	 return;
    }
    else if(text == tr("English"))
    {
	    qDebug()<<text;
	    char *pLang = getenv( "LANG" );
	    assert(NULL != pLang);
	    if(0 != strncmp("en_US", pLang, 5))
	    {
		    system("/usr/local/qtex/bin/language en_US &");
	    }
	 return;
    }
    else if(text == QString::fromUtf8("繁體中文"))
    {
	    qDebug()<<text;
	    char *pLang = getenv( "LANG" );
	    assert(NULL != pLang);
	    if(0 != strncmp("zh_TW", pLang, 5))
	    {	
		    system("/usr/local/qtex/bin/language zh_TW &");
	    }
	 return;
    }
    else if(text == QString::fromUtf8("简体中文"))
    {
	    qDebug()<<text;
	    char *pLang = getenv( "LANG" );
	    assert(NULL != pLang);
	    if(0 != strncmp("zh_CN", pLang, 5))
	    {	
		    system("/usr/local/qtex/bin/language zh_CN &");
	    }
	 return;
    }
    else if(text == QString::fromUtf8("日本語"))
    {
	    qDebug()<<text;
	    char *pLang = getenv( "LANG" );
	    assert(NULL != pLang);
	    if(0 != strncmp("ja_JP", pLang, 5))
	    {	
		    system("/usr/local/qtex/bin/language ja_JP &");
	    }
	 return;
    }
    else if(text == tr("Device Shut Down"))
    {
	    qDebug()<<text;
	    return;
    }
    else if(text == tr("Screen Saver")
	    || text == tr("Screen Saver Off")
	    ||text == tr("Screen Saver On"))
    {
	    qDebug()<<text;
	    bool ScreenSaverFlag = true;
	    if(false == ScreenSaverFlag)
	    {
		    ScreenSaverFlag = true;
		    item->setText(tr("Screen Saver Off"));
	    }	
	    else
	    {
		    ScreenSaverFlag = false;
		    item->setText(tr("Screen Saver On"));
	    }
	 return;
    }
    else if(text == tr("Restore Defaults"))
    {
	    qDebug()<<text;
	 return;
    }
    else if(text == tr("About"))
    {
	    qDebug()<<text;
	 return;
    }
}

void PlatformServerInterface::showSearchFrame()
{
	searchWindow->setWindowTitle(tr("Search"));
	searchWindow->showMaximized();
}

void PlatformServerInterface::OnDocumentSearchClicked()
{
    /*
    if(NULL != searchLine->text())
    {
        QString documentpar;
        QContent *documentview = new QContent();
        documentview->setName(tr("Documents"));
        documentview->setType("Folder/Documents");
        documentview->setIcon("qpe/DocsIcon"); 
//        documentSearchContent = searchLine->text();
        documentpar = searchLine->text();
	 execContent(*documentview);//src/server/phone/ui/browserstack/
// add by liulijun s 091221
        qDebug()<<__PRETTY_FUNCTION__;
        QDataStream stream(new QBuffer);
        stream.device()->open(QIODevice::WriteOnly);
        stream<< documentpar;
        QByteArray data = ((QBuffer*)stream.device())->buffer();
        QtopiaChannel::send("QPE/Liulijun", "Document Search", data);
	QtopiaChannel::flush(); // zhu-chh 091223
// add by liulijun e 091221
	 searchWindow->hide();
    }
    */
}

void PlatformServerInterface::OnMp3SearchClicked()
{
    if(NULL != searchLine->text())
    {
        std::string stringText = searchLine->text().toLocal8Bit().data();
	 std::string stringCmd = "/usr/local/qtex/bin/mediaplayer " + stringText + " &";
    }
}

void PlatformServerInterface::defaultButtons()
{
    /*=========================================================================
    Available keys:
        left, top, width, height, entry, exeargs, 
        icon, title, titlefontsize, text, textfontsize.
    NOTE: `entry` is like what in defaultbuttons.conf
    =========================================================================*/
    QSettings settings(QSettings::SystemScope, "Trolltech","HomeDesktop");
    // set default values.
    settings.beginGroup("button0");
    settings.setValue("left", "159");
    settings.setValue("top", "58");
    settings.setValue("width", "default");
    settings.setValue("height", "default");
    settings.setValue("entry", "Applications/ebookreader.desktop");
    settings.setValue("exeargs", "showBooks");
    settings.setValue("icon", "pics/qpe/button0.png");
    settings.setValue("title", "Continue Reading");
    settings.setValue("titlefontsize", "7");
    settings.setValue("text", "");
    settings.setValue("textfontsize", "6");
    settings.endGroup();
    
    settings.beginGroup("button1");
    settings.setValue("left", "65");
    settings.setValue("top", "289");
    settings.setValue("width", "default");
    settings.setValue("height", "default");
    settings.setValue("entry", "Applications/ebookreader.desktop");
    settings.setValue("icon", "pics/qpe/button1.png");
    settings.setValue("title", "Books");
    settings.setValue("titlefontsize", "7");
    settings.setValue("text", "");
    settings.setValue("textfontsize", "6");
    settings.endGroup();
    
    settings.beginGroup("button2");
    settings.setValue("left", "326");
    settings.setValue("top", "289");
    settings.setValue("width", "default");
    settings.setValue("height", "default");
    settings.setValue("entry", "Applications/mediaplayer.desktop");
    settings.setValue("icon", "pics/qpe/button2.png");
    settings.setValue("title", "Music");
    settings.setValue("titlefontsize", "7");
    settings.setValue("text", "");
    settings.setValue("textfontsize", "6");
    settings.endGroup();
    
    settings.beginGroup("button3");
    settings.setValue("left", "65");
    settings.setValue("top", "499");
    settings.setValue("width", "default");
    settings.setValue("height", "default");
    settings.setValue("entry", "Documents");
    settings.setValue("icon", "pics/qpe/button3.png");
    settings.setValue("title", "Documents");
    settings.setValue("titlefontsize", "7");
    settings.setValue("text", "");
    settings.setValue("textfontsize", "6");
    settings.endGroup();
    
    settings.beginGroup("button4");
    settings.setValue("left", "326");
    settings.setValue("top", "499");
    settings.setValue("width", "default");
    settings.setValue("height", "default");
    settings.setValue("entry", "Applications/sketch.desktop");
    settings.setValue("icon", "pics/qpe/button4.png");
    settings.setValue("title", "Notes");
    settings.setValue("titlefontsize", "7");
    settings.setValue("text", "");
    settings.setValue("textfontsize", "6");
    settings.endGroup();
    
    settings.sync();
}

QTOPIA_REPLACE_WIDGET(QAbstractServerInterface, PlatformServerInterface)
