#include <QApplication>
#include <QWidget>

//这个文件必须包含用于动态加载ui.
#include <QtUiTools>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	//加载ui文件
	QUiLoader loader;
	QFile file("./untitled.ui");
	file.open(QFile::ReadOnly);

	//根据ui文件生成界面
	//load的第2个参数是父部件
	QWidget *uiWidget = loader.load(&file, 0);
	file.close();
	uiWidget->show();

	//根据名称获得子部件的示例代码
	//ui_Button = qFindChild<QPushButton*>(this,"name1");
	//ui_textEdit = qFindChild<QTextEdit*>(this, "name2");
	//ui_lineEdit = qFindChild<QLineEdit*>(this, "name3");

	return app.exec();
}
