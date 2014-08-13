/****************************************************************************
** Meta object code from reading C++ file 'popupim.h'
**
** Created: Fri Oct 23 11:05:26 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "popupim.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'popupim.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PopupIM[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      48,    9,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_PopupIM[] = {
    "PopupIM\0\0unicode,keycode,modifiers,press,repeat\0"
    "keyPress(ushort,ushort,ushort,bool,bool)\0"
};

const QMetaObject PopupIM::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PopupIM,
      qt_meta_data_PopupIM, 0 }
};

const QMetaObject *PopupIM::metaObject() const
{
    return &staticMetaObject;
}

void *PopupIM::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PopupIM))
        return static_cast<void*>(const_cast< PopupIM*>(this));
    return QWidget::qt_metacast(_clname);
}

int PopupIM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: keyPress((*reinterpret_cast< ushort(*)>(_a[1])),(*reinterpret_cast< ushort(*)>(_a[2])),(*reinterpret_cast< ushort(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void PopupIM::keyPress(ushort _t1, ushort _t2, ushort _t3, bool _t4, bool _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_PopupPushButton[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      22,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      63,   16,   16,   16, 0x08,
      81,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PopupPushButton[] = {
    "PopupPushButton\0\0,,,,\0"
    "keyPress(ushort,ushort,ushort,bool,bool)\0"
    "sendKeyForPress()\0sendKeyForRelease()\0"
};

const QMetaObject PopupPushButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_PopupPushButton,
      qt_meta_data_PopupPushButton, 0 }
};

const QMetaObject *PopupPushButton::metaObject() const
{
    return &staticMetaObject;
}

void *PopupPushButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PopupPushButton))
        return static_cast<void*>(const_cast< PopupPushButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int PopupPushButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: keyPress((*reinterpret_cast< ushort(*)>(_a[1])),(*reinterpret_cast< ushort(*)>(_a[2])),(*reinterpret_cast< ushort(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 1: sendKeyForPress(); break;
        case 2: sendKeyForRelease(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void PopupPushButton::keyPress(ushort _t1, ushort _t2, ushort _t3, bool _t4, bool _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
