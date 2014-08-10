#include <QModelIndex>
#include <QVariant>
#include "mystringlistmodel.h"

int MyStringListModel::rowCount(const QModelIndex &parent) const
{
    return stringList.count();
}


QVariant MyStringListModel::data(const QModelIndex &index, int role) const
{//根据不同角色，返回不同的数据，这里只支持一个角色：Qt::DisplayRole
    if (!index.isValid())
        return QVariant();

    if (index.row() >= stringList.size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return stringList.at(index.row());
    else
        return QVariant();
}


QVariant MyStringListModel::headerData(int section, Qt::Orientation orientation, int role) const
{//头部的显示信息增加界面友好性
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

Qt::ItemFlags MyStringListModel::flags(const QModelIndex &index) const
{//判断数据项是否可编辑可编辑则创建delegate editor.
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool MyStringListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{//这里用来设置数据项，此函数由delegate发起调用
    if (index.isValid() && role == Qt::EditRole) {

        stringList.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool MyStringListModel::insertRows(int position, int rows, const QModelIndex &parent)
{//beginInsertRows()通知其他组件行数将会改变。endInsertRows()对操作进行确认与通知。返回true表示成功。
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        stringList.insert(position, "");
    }

    endInsertRows();
    return true;
}

bool MyStringListModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        stringList.removeAt(position);
    }

    endRemoveRows();
    return true;
}
