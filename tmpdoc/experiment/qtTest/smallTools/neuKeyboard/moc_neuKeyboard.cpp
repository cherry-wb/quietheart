/****************************************************************************
** Meta object code from reading C++ file 'neuKeyboard.h'
**
** Created: Wed Dec 23 09:46:38 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "neuKeyboard.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'neuKeyboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NeuKeyboard[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      58,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     112,  108,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NeuKeyboard[] = {
    "NeuKeyboard\0\0unicode,keycode,modifiers,isPress,autoRepeat\0"
    "keyPress(int,int,Qt::KeyboardModifiers,bool,bool)\0"
    "key\0sendKey(QString)\0"
};

const QMetaObject NeuKeyboard::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NeuKeyboard,
      qt_meta_data_NeuKeyboard, 0 }
};

const QMetaObject *NeuKeyboard::metaObject() const
{
    return &staticMetaObject;
}

void *NeuKeyboard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NeuKeyboard))
        return static_cast<void*>(const_cast< NeuKeyboard*>(this));
    return QWidget::qt_metacast(_clname);
}

int NeuKeyboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: keyPress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< Qt::KeyboardModifiers(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 1: sendKey((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void NeuKeyboard::keyPress(int _t1, int _t2, Qt::KeyboardModifiers _t3, bool _t4, bool _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
