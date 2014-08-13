/****************************************************************************
** Meta object code from reading C++ file 'imframe.h'
**
** Created: Wed Nov 4 15:57:37 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/imframe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IMFrame[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      20,    9,    8,    8, 0x08,
      45,   41,    8,    8, 0x08,
      74,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_IMFrame[] = {
    "IMFrame\0\0newContent\0sendContent(QString)\0"
    "key\0sendKeyBoardContent(QString)\0"
    "confirmContent()\0"
};

const QMetaObject IMFrame::staticMetaObject = {
    { &QWSInputMethod::staticMetaObject, qt_meta_stringdata_IMFrame,
      qt_meta_data_IMFrame, 0 }
};

const QMetaObject *IMFrame::metaObject() const
{
    return &staticMetaObject;
}

void *IMFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IMFrame))
        return static_cast<void*>(const_cast< IMFrame*>(this));
    return QWSInputMethod::qt_metacast(_clname);
}

int IMFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWSInputMethod::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendContent((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: sendKeyBoardContent((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: confirmContent(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
