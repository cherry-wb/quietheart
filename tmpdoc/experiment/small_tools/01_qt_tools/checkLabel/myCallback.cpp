#include "myCallback.h"
#include <QFont>
#include <QPixmap>
#include <QHBoxLayout>
#include <QDebug>
ECheckLabel::ECheckLabel(QString &text, QWidget *parent, Qt::WindowFlags f)
:QWidget(parent, f)
{   
	isCheck = 0;   

	iconLabel = new EPushLabel(QString(""));
	iconLabel->setScaledContents(true);
	iconLabel->setPixmap(QPixmap((const char **)unChecked_xpm));
	textLabel = new EPushLabel(text);

	connect(iconLabel,SIGNAL(pressSignal()), this, SLOT(checked()));
	connect(textLabel,SIGNAL(pressSignal()), this, SLOT(checked()));

	//init();
	updateLayout();
}   
void ECheckLabel::init()
{
	;
}

void ECheckLabel::updateLayout()
{
	qDebug()<<"@@@@@@@{"<<__PRETTY_FUNCTION__;
	QHBoxLayout *hl = new QHBoxLayout();
	setLayout(hl);
	qDebug()<<"hello!";

	hl->addWidget(iconLabel);
	hl->addWidget(textLabel);
	qDebug()<<"@@@@@@@}"<<__PRETTY_FUNCTION__;
}
void ECheckLabel::setIconSize(const QSize &s)
{
	iconLabel->setFixedSize(s);
}
QFont ECheckLabel::font()
{
	return textLabel->font();
}
void ECheckLabel::setFont(const QFont &f)
{
	textLabel->setFont(f);
}

int ECheckLabel::checkValue()
{
	return isCheck;
}
QString ECheckLabel::text()
{
	qDebug()<<"@@@@@@@{"<<__PRETTY_FUNCTION__;
	return textLabel->text();
	qDebug()<<"@@@@@@@}"<<__PRETTY_FUNCTION__;
}

void ECheckLabel::checked()
{
	if(isCheck == 1)
	{
		iconLabel->setPixmap(QPixmap((const char **)unChecked_xpm));
		isCheck = 0;
	}
	else
	{
		iconLabel->setPixmap(QPixmap((const char **)checked_xpm));
		isCheck = 1;
	}
	emit stateChanged(isCheck);
}
//checked icon
const char * ECheckLabel::checked_xpm[] = {
"40 40 68 1",
" 	c None",
".	c #231F20",
"+	c #DBDBDB",
"@	c #E9E9E9",
"#	c #433F40",
"$	c #5B5859",
"%	c #C6C5C6",
"&	c #989797",
"*	c #252122",
"=	c #858383",
"-	c #353132",
";	c #A8A6A7",
">	c #868484",
",	c #4E4B4C",
"'	c #D6D6D6",
")	c #2C2929",
"!	c #747172",
"~	c #615E5F",
"{	c #CAC9C9",
"]	c #262323",
"^	c #737071",
"/	c #BAB9BA",
"(	c #E8E8E8",
"_	c #BFBFBF",
":	c #CDCCCD",
"<	c #A8A7A7",
"[	c #929090",
"}	c #272324",
"|	c #4A4748",
"1	c #E5E5E5",
"2	c #3F3C3C",
"3	c #6A6868",
"4	c #767475",
"5	c #959394",
"6	c #423E3F",
"7	c #A2A0A1",
"8	c #A7A5A6",
"9	c #DEDEDE",
"0	c #343031",
"a	c #6F6D6E",
"b	c #2F2B2C",
"c	c #CFCECE",
"d	c #838181",
"e	c #514E4F",
"f	c #454242",
"g	c #D5D4D4",
"h	c #2B2728",
"i	c #242021",
"j	c #2B2829",
"k	c #777575",
"l	c #A19FA0",
"m	c #C8C7C7",
"n	c #262223",
"o	c #6F6C6D",
"p	c #D0CFCF",
"q	c #5E5B5B",
"r	c #E1E1E1",
"s	c #434041",
"t	c #2E2A2B",
"u	c #9F9E9E",
"v	c #373334",
"w	c #6D6A6B",
"x	c #423F40",
"y	c #C9C8C8",
"z	c #9D9C9C",
"A	c #585555",
"B	c #535050",
"C	c #4C4949",
"                                        ",
"                                        ",
"                                        ",
"   ...................................  ",
"   ...................................  ",
"   ...................................  ",
"   ...                             ...  ",
"   ...                             ...  ",
"   ...                       +@    ...  ",
"   ...                       #$%   ...  ",
"   ...                      &..*=  ...  ",
"   ...                      -...;  ...  ",
"   ...                     >...,   ...  ",
"   ...                    ')...    ...  ",
"   ...                    !...~    ...  ",
"   ...                   {]..]     ...  ",
"   ...                   ~...^     ...  ",
"   ...                  /...)      ...  ",
"   ...                 (,...>      ...  ",
"   ...     _:          <...-       ...  ",
"   ...    [}|         12...        ...  ",
"   ...   3...4        5...6        ...  ",
"   ...   7....8      90...         ...  ",
"   ...    a...bc    @d...e         ...  ",
"   ...     f...|    gh..i          ...  ",
"   ...     {j...k  @a...           ...  ",
"   ...      l....< mn..}           ...  ",
"   ...       o...bpq...            ...  ",
"   ...       rs.......t            ...  ",
"   ...        {h......             ...  ",
"   ...         u.....v             ...  ",
"   ...          w....              ...  ",
"   ...          rx..               ...  ",
"   ...           yh.               ...  ",
"   ...            z                ...  ",
"   ...................................  ",
"   ...................................  ",
"   ...................................  ",
"   ...................................  ",
"                                        "};

//unchecked icon
const char * ECheckLabel::unChecked_xpm[] = {
"37 39 6 1",
" 	c None",
".	c #5E5B5B",
"+	c #231F20",
"@	c #DDDDDD",
"#	c #312D2E",
"$	c #252122",
"                                     ",
"                                     ",
" ................................... ",
" +++++++++++++++++++++++++++++++++++ ",
" +++++++++++++++++++++++++++++++++++ ",
" +++++++++++++++++++++++++++++++++++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++                             +++ ",
" +++++++++++++++++++++++++++++++++++ ",
" +++++++++++++++++++++++++++++++++++ ",
" +++++++++++++++++++++++++++++++++++ ",
"                                     ",
"                                     "};
