/****************************************************************************
** Meta object code from reading C++ file 'mylist.h'
**
** Created: Sun Feb 21 11:44:07 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mylist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mylist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyListItem[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      17,   12,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_MyListItem[] = {
    "MyListItem\0\0item\0clicked(MyListItem*)\0"
};

const QMetaObject MyListItem::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MyListItem,
      qt_meta_data_MyListItem, 0 }
};

const QMetaObject *MyListItem::metaObject() const
{
    return &staticMetaObject;
}

void *MyListItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyListItem))
        return static_cast<void*>(const_cast< MyListItem*>(this));
    return QWidget::qt_metacast(_clname);
}

int MyListItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clicked((*reinterpret_cast< MyListItem*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void MyListItem::clicked(MyListItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_MyList[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      13,    8,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyList[] = {
    "MyList\0\0item\0clickResponse(MyListItem*)\0"
};

const QMetaObject MyList::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MyList,
      qt_meta_data_MyList, 0 }
};

const QMetaObject *MyList::metaObject() const
{
    return &staticMetaObject;
}

void *MyList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyList))
        return static_cast<void*>(const_cast< MyList*>(this));
    return QWidget::qt_metacast(_clname);
}

int MyList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clickResponse((*reinterpret_cast< MyListItem*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
