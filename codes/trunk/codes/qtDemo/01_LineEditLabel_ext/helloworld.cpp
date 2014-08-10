/* 程序功能：只有一个窗口的helloworld程序。
 * 窗口内有一个标签一个编辑条。按标签上面的快捷键则编辑条获得键盘焦点。
 * */
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
int main( int argc, char **argv )
{
	QApplication a( argc, argv );

	QWidget window;
	window.resize(320, 240);

	//建立编辑条
	QLineEdit edit(&window);
	edit.move(200,50);
	QLineEdit edit2(&window);
	edit2.move(200,200);

	//建立一个标签
	QLabel label("&first",&window);
	//指定若按标签快捷键对应的获得键盘焦点的构件
	label.setBuddy(&edit);
	label.move(100,50);

	window.show();
	return a.exec();
}

