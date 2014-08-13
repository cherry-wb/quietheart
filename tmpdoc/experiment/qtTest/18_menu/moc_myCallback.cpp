/****************************************************************************
** Meta object code from reading C++ file 'myCallback.h'
**
** Created: Fri Aug 20 10:15:14 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "myCallback.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myCallback.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyCallback[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x09,
      18,   11,   11,   11, 0x09,
      24,   11,   11,   11, 0x09,
      30,   11,   11,   11, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_MyCallback[] = {
    "MyCallback\0\0do1()\0do2()\0do3()\0"
    "isChecked(bool)\0"
};

const QMetaObject MyCallback::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MyCallback,
      qt_meta_data_MyCallback, 0 }
};

const QMetaObject *MyCallback::metaObject() const
{
    return &staticMetaObject;
}

void *MyCallback::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyCallback))
        return static_cast<void*>(const_cast< MyCallback*>(this));
    return QWidget::qt_metacast(_clname);
}

int MyCallback::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: do1(); break;
        case 1: do2(); break;
        case 2: do3(); break;
        case 3: isChecked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
