#ifndef MY_STRLST_MODEL
#define MY_STRLST_MODEL
#include <QAbstractListModel>
#include <QModelIndex>
#include <QVariant>
#include <QStringList>

class MyStringListModel : public QAbstractListModel
{
    Q_OBJECT
    public:
        MyStringListModel(const QStringList &strings, QObject *parent = 0): QAbstractListModel(parent), stringList(strings) {}
        int rowCount(const QModelIndex &parent = QModelIndex()) const;//返回model中的行数
        QVariant data(const QModelIndex &index, int role) const;//返回与特定model index对应的数据项
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;//views在标题中显示的数据

        Qt::ItemFlags flags(const QModelIndex &index) const;//返回特定的数据项是否可编辑
        bool setData(const QModelIndex &index,const QVariant &value, int role);//设置特定的数据项
        bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());//插入行
        bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());//删除行

    private:
        QStringList stringList;//数据内容
};
#endif
