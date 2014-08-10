/* 程序功能：实现多语言
(0)源代码需要支持多语言的字符串，全用QObject::tr("xxx")来包含，并用qmake -project生成xxx.pro的工程文件
$qmake -project

(1)在xxx.pro文件中加入
TRANSLATIONS = Language_Chn.ts    # 1个或者多个ts文件名

(2)在命令行执行：
$lupdate xxx.pro  # 生成ts文件
这里，ts文件会在源代码中的相应位置生成，而不是build目录。

(3)对ts文件中的内容进行翻译
编辑ts文件，在每一项<translation type="unfinished">后面加入对应<source>的翻译语言，并将"unfinished"改为"finished"。
例如如下ts文件，修改完可以得到：
<message>
<location filename="helloworld.cpp" line="73"/>
<source>Audio</source>
<translation type="finished">声音</translation>
</message>
这里,各种语言初始的ts文件都是一样的.如果某些选项不需要翻译，可以不进行编辑。

(4)以ts为输入，生成qm文件
$lrelease xxx.pro
或$lrelease Language_Chn.qm
这里，生成的xxx.qm文件就是程序加载时使用的翻译文件，注意：qt的linguist可以继续在这个qm文件上编辑。

(5)增加代码
QTranslator qtTranslator;
qtTranslator.load("Language_Chn");
a.installTranslator(&qtTranslator);

(6)编译运行
Language_Chn.qm文件放在程序运行目录
$qmake
$make
$./<运行>
 * */
#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTranslator>
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

    QTranslator qtTranslator;
    qtTranslator.load("Language_Chn");
    a.installTranslator(&qtTranslator);

	QWidget window;
	window.resize(320, 240);

	//建立一个标签
	QLabel label(QObject::tr("Audio"),&window);
	label.move(100,50);

	window.show();//这里，由于前面QTranslator的加载，显示的标签是翻译好的"声音"而非"Audio"
	return a.exec();
}

