/* 程序功能：窗口内有三个label.
 * 这里设置每个label的比例大小。
 * 设置每个控件占据总大小的比例，使用setStretchFactor
 * */
#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	QWidget window;
	window.resize(320, 240);

	QHBoxLayout *hlayout = new QHBoxLayout;
	QLabel *label1 = new QLabel(QObject::tr("Name1"));
	label1->setFrameShape(QFrame::StyledPanel);
	QLabel *label2 = new QLabel(QObject::tr("Name2"));
	label2->setFrameShape(QFrame::StyledPanel);
	QLabel *label3 = new QLabel(QObject::tr("Name3"));
	label3->setFrameShape(QFrame::StyledPanel);

	//设置控件按照比例的大小。但是不会比最小者小了。
	//根据自己的理解，这里的数字表示控件占有的总控件的比例，这里总空间就是1+2+3.
	//如果设置的是0的话应该使用的是空间的最小大小，因为无法再小了。
	//所以如其中一个是0那么其他的factor应把除了这个最小的空间之外所有的空间占据并分配。
	hlayout->addWidget(label1);
	hlayout->setStretchFactor(label1,1);
	hlayout->addWidget(label2);
	hlayout->setStretchFactor(label2,2);
	//hlayout->addStretch(0);//添加了一个空白
	hlayout->addWidget(label3);
	hlayout->setStretchFactor(label3,3);


	window.show();
	window.setLayout(hlayout);//这里设置选用哪个布局

	return a.exec();
}

