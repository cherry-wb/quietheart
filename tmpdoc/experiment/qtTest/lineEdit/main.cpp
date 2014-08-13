#include <QApplication>
#include <QLineEdit>
#include <QString>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLineEdit line;
    line.setText("input");
    line.show();
    return app.exec();
}
