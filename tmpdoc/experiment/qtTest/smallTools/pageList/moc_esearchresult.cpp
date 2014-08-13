/****************************************************************************
** Meta object code from reading C++ file 'esearchresult.h'
**
** Created: Thu Mar 11 16:39:38 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "esearchresult.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'esearchresult.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ESearch[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      29,    8,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ESearch[] = {
    "ESearch\0\0pageCntChanged(int)\0"
    "pageSelected(int)\0"
};

const QMetaObject ESearch::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ESearch,
      qt_meta_data_ESearch, 0 }
};

const QMetaObject *ESearch::metaObject() const
{
    return &staticMetaObject;
}

void *ESearch::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ESearch))
        return static_cast<void*>(const_cast< ESearch*>(this));
    return QWidget::qt_metacast(_clname);
}

int ESearch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pageCntChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: pageSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ESearch::pageCntChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ESearch::pageSelected(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_EItemContainer[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,   36,   15,   15, 0x0a,
      59,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_EItemContainer[] = {
    "EItemContainer\0\0pageCntChanged(int)\0"
    "page\0pageSelected(int)\0refresh()\0"
};

const QMetaObject EItemContainer::staticMetaObject = {
    { &QStackedWidget::staticMetaObject, qt_meta_stringdata_EItemContainer,
      qt_meta_data_EItemContainer, 0 }
};

const QMetaObject *EItemContainer::metaObject() const
{
    return &staticMetaObject;
}

void *EItemContainer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EItemContainer))
        return static_cast<void*>(const_cast< EItemContainer*>(this));
    return QStackedWidget::qt_metacast(_clname);
}

int EItemContainer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStackedWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pageCntChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: pageSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: refresh(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void EItemContainer::pageCntChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_ESearchItem[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_ESearchItem[] = {
    "ESearchItem\0"
};

const QMetaObject ESearchItem::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ESearchItem,
      qt_meta_data_ESearchItem, 0 }
};

const QMetaObject *ESearchItem::metaObject() const
{
    return &staticMetaObject;
}

void *ESearchItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ESearchItem))
        return static_cast<void*>(const_cast< ESearchItem*>(this));
    return QWidget::qt_metacast(_clname);
}

int ESearchItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_EPageBar[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      28,    9,    9,    9, 0x0a,
      48,    9,    9,    9, 0x0a,
      64,    9,    9,    9, 0x0a,
      78,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_EPageBar[] = {
    "EPageBar\0\0pageSelected(int)\0"
    "pageCntChanged(int)\0pageSelect(int)\0"
    "nextPageBtn()\0lastPageBtn()\0"
};

const QMetaObject EPageBar::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_EPageBar,
      qt_meta_data_EPageBar, 0 }
};

const QMetaObject *EPageBar::metaObject() const
{
    return &staticMetaObject;
}

void *EPageBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EPageBar))
        return static_cast<void*>(const_cast< EPageBar*>(this));
    return QFrame::qt_metacast(_clname);
}

int EPageBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pageSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: pageCntChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: pageSelect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: nextPageBtn(); break;
        case 4: lastPageBtn(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void EPageBar::pageSelected(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_EPushLabel[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_EPushLabel[] = {
    "EPushLabel\0\0pressSignal()\0"
};

const QMetaObject EPushLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_EPushLabel,
      qt_meta_data_EPushLabel, 0 }
};

const QMetaObject *EPushLabel::metaObject() const
{
    return &staticMetaObject;
}

void *EPushLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EPushLabel))
        return static_cast<void*>(const_cast< EPushLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int EPushLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pressSignal(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void EPushLabel::pressSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
