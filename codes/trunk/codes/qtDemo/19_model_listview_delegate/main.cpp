/*程序功能：使用model/view模式，以QListView显示字符串列表。
model，与数据源通讯，并提供接口给结构中的别的组件使用。通讯的性质依赖于数据源的种类与model实现的方式。
view，从model获取model indexes,通过model indexes，view可以从model数据源中获取数据并组织。
delegate，会在标准的views中对数据项进行进一步渲染或编辑，当某个数据项被选中时，delegate通过model indexes与model直接进行交流。
models,views,delegates之间通过信号，槽机制来进行通讯。
本例使用自己定义的model，标准的QListView，以及自己定义的delegate来达到程序功能。delegate其实就是一个自定义的构件，显示在QListView中，此方式比较灵活。
*/
#include <QApplication>
#include <QAbstractItemModel>
#include <QStringList>
#include <QListView>

#include "mystringlistmodel.h"
#include "lineeditdelegate.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //view
    QListView *view = new QListView;

    //delegate
    QItemDelegate *delegate = new LineEditDelegate;

    //model
    QStringList numbers;
    numbers << "One" << "Two" << "Three" << "Four" << "Five";
    QAbstractItemModel *model = new MyStringListModel(numbers);

    view->setModel(model);
    view->setItemDelegate(delegate);
    view->show();
    return app.exec();
}
