/****************************************************************************
** Meta object code from reading C++ file 'dialogpages.h'
**
** Created: Thu Mar 1 15:17:34 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/dialogpages.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogpages.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CreateNewPage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CreateNewPage[] = {
    "CreateNewPage\0\0diagram_enum\0"
    "return_to_parent(int)\0ButtonClicked()\0"
};

void CreateNewPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CreateNewPage *_t = static_cast<CreateNewPage *>(_o);
        switch (_id) {
        case 0: _t->return_to_parent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->ButtonClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CreateNewPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CreateNewPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CreateNewPage,
      qt_meta_data_CreateNewPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CreateNewPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CreateNewPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CreateNewPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CreateNewPage))
        return static_cast<void*>(const_cast< CreateNewPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int CreateNewPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CreateNewPage::return_to_parent(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_CreateOpenPage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      51,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CreateOpenPage[] = {
    "CreateOpenPage\0\0diagram_enum\0"
    "return_to_parent(int)\0OpenFileInit()\0"
};

void CreateOpenPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CreateOpenPage *_t = static_cast<CreateOpenPage *>(_o);
        switch (_id) {
        case 0: _t->return_to_parent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->OpenFileInit(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CreateOpenPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CreateOpenPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CreateOpenPage,
      qt_meta_data_CreateOpenPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CreateOpenPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CreateOpenPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CreateOpenPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CreateOpenPage))
        return static_cast<void*>(const_cast< CreateOpenPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int CreateOpenPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CreateOpenPage::return_to_parent(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
