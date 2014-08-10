/*程序功能：
一个splitter控件，如果有两个widget以splitter为父窗口，那么这两个窗口中间会有一个分割条。
*/
#include <QApplication>
#include <QSplitter>
#include <QLabel>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSplitter *splitter = new QSplitter;
	
	QLabel *lbl1 = new QLabel("test1",splitter);
	QLabel *lbl2 = new QLabel("test2",splitter);

    splitter->setWindowTitle("Two views onto the same directory model");
    splitter->show();
    return app.exec();
	delete splitter;
}
