#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
//#include <qgridlayout.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include "lcdRange.h"
#include "cannon.h"
#include "myWidget.h"
MyWidget::MyWidget( QWidget *parent, const char *name )
: QWidget( parent, name )
{
	//pushbutton
	//两种建立的方法都行
	//QPushButton *quit = new QPushButton( "Quit", this, "quit" );
	//这里的tr是便于多语言使用的QObject::tr();
	QPushButton *quit = new QPushButton(tr("Quit"));
	quit->setFont( QFont( "Times", 18, QFont::Bold ) );
	connect( quit, SIGNAL(clicked()), qApp, SLOT(quit()) );

	//lcdrange
	//两种建立的方法都行
	//LCDRange *angle = new LCDRange( this, "angle" );
	LCDRange *angle = new LCDRange;
	angle->setRange( 5, 70 );

	//cannonfield
	//两种建立的方法都行
	//CannonField *cannonField = new CannonField( this, "cannonField" );
	CannonField *cannonField = new CannonField;
	connect( angle, SIGNAL(valueChanged(int)),
			cannonField, SLOT(setAngle(int)) );
	connect( cannonField, SIGNAL(angleChanged(int)),
			angle, SLOT(setValue(int)) );

	//gridlayout
	//需要注意的是this的基类不能是layout了，如vbox
	Q3GridLayout *grid = new Q3GridLayout( this, 2, 2, 10 );
	
	//网格的左上的单元格中加入一个Quit按钮：0,0。 
	grid->addWidget( quit, 0, 0 );

	//把angle这个LCDRange放到左下的单元格，在单元格内向上对齐。
	grid->addWidget( angle, 1, 0, Qt::AlignTop );

	grid->addWidget( cannonField, 1, 1 );

	//告诉QGridLayout右边的列（列1）是可拉伸的。
	//因为左边的列不是（它的拉伸因数是0，这是默认值），QGridLayout就会在MyWidget被重新定义大小的时候试图让左面的窗口部件大小不变，而重新定义CannonField的大小。 
	grid->setColStretch( 1, 10 );

	angle->setValue( 60 );
	angle->setFocus();
}
