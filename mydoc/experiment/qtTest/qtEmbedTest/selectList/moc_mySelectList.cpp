/****************************************************************************
** Meta object code from reading C++ file 'mySelectList.h'
**
** Created: Fri Oct 30 17:22:44 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mySelectList.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mySelectList.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MySelectList[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      22,   13,   14,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_MySelectList[] = {
    "MySelectList\0\0QString\0selBtn(QString)\0"
};

const QMetaObject MySelectList::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MySelectList,
      qt_meta_data_MySelectList, 0 }
};

const QMetaObject *MySelectList::metaObject() const
{
    return &staticMetaObject;
}

void *MySelectList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MySelectList))
        return static_cast<void*>(const_cast< MySelectList*>(this));
    return QWidget::qt_metacast(_clname);
}

int MySelectList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { QString _r = selBtn((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
