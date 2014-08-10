#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
#include <q3grid.h>
#include "lcdRange.h"
#include"myWidget.h"
MyWidget::MyWidget( QWidget *parent, const char *name )
: Q3VBox( parent, name )
{
	QPushButton *quit = new QPushButton( "Quit", this, "quit" );
	quit->setFont( QFont( "Times", 18, QFont::Bold ) );
	connect( quit, SIGNAL(clicked()), qApp, SLOT(quit()) );
	Q3Grid *grid = new Q3Grid( 4, this );
	LCDRange *previous = 0;
	for( int r = 0 ; r < 4 ; r++ )
		for( int c = 0 ; c < 4 ; c++ )
		{
			LCDRange* lr = new LCDRange( grid );
			if ( previous )
			{
				//这里设置拖动后一个滑块会调用前一个滑块的setValue函数。
				connect( lr, SIGNAL(valueChanged(int)),
						previous, SLOT(setValue(int)) );
			}
			previous = lr;

		}
}
