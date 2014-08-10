#include <QItemDelegate>
#include <QObject>
#include <QWidget>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QLineEdit>
#include "lineeditdelegate.h"

LineEditDelegate::LineEditDelegate(QObject *parent):QItemDelegate(parent)
{
}

QWidget *LineEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

void LineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::DisplayRole).toString();

    QLineEdit *line = static_cast<QLineEdit*>(editor);
    line->setText(text);
}

void LineEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *line = static_cast<QLineEdit*>(editor);
    QString text = line->text();
    model->setData(index, text);
    //emit closeEditor(line);
}

void LineEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
