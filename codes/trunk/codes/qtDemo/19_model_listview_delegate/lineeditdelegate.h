#ifndef LINE_EDITDELEGATE_H
#define LINE_EDITDELEGATE_H
#include <QItemDelegate>
#include <QObject>
#include <QWidget>
#include <QStyleOptionViewItem>
#include <QModelIndex>

class LineEditDelegate : public QItemDelegate
{
    Q_OBJECT

    public:
        LineEditDelegate(QObject *parent = 0);
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;//提供编辑器
        void setEditorData(QWidget *editor, const QModelIndex &index) const;//用编辑器渲染model的data
        void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;//向model提交修改的data。
        void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;//更新编辑器几何布局
};

#endif
