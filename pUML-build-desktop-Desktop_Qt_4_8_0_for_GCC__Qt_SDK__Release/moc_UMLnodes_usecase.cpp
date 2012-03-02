/****************************************************************************
** Meta object code from reading C++ file 'UMLnodes_usecase.h'
**
** Created: Thu Mar 1 15:17:35 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/UMLnodes_usecase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UMLnodes_usecase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StickPersonObjectDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_StickPersonObjectDialog[] = {
    "StickPersonObjectDialog\0"
};

void StickPersonObjectDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData StickPersonObjectDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject StickPersonObjectDialog::staticMetaObject = {
    { &QInputDialog::staticMetaObject, qt_meta_stringdata_StickPersonObjectDialog,
      qt_meta_data_StickPersonObjectDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StickPersonObjectDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StickPersonObjectDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StickPersonObjectDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StickPersonObjectDialog))
        return static_cast<void*>(const_cast< StickPersonObjectDialog*>(this));
    return QInputDialog::qt_metacast(_clname);
}

int StickPersonObjectDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QInputDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_StickPersonObject[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   19,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_StickPersonObject[] = {
    "StickPersonObject\0\0newName\0setName(QString)\0"
};

void StickPersonObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StickPersonObject *_t = static_cast<StickPersonObject *>(_o);
        switch (_id) {
        case 0: _t->setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData StickPersonObject::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject StickPersonObject::staticMetaObject = {
    { &ObjectNode::staticMetaObject, qt_meta_stringdata_StickPersonObject,
      qt_meta_data_StickPersonObject, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StickPersonObject::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StickPersonObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StickPersonObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StickPersonObject))
        return static_cast<void*>(const_cast< StickPersonObject*>(this));
    return ObjectNode::qt_metacast(_clname);
}

int StickPersonObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ObjectNode::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_OvalObjectDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_OvalObjectDialog[] = {
    "OvalObjectDialog\0"
};

void OvalObjectDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData OvalObjectDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject OvalObjectDialog::staticMetaObject = {
    { &QInputDialog::staticMetaObject, qt_meta_stringdata_OvalObjectDialog,
      qt_meta_data_OvalObjectDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OvalObjectDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OvalObjectDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OvalObjectDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OvalObjectDialog))
        return static_cast<void*>(const_cast< OvalObjectDialog*>(this));
    return QInputDialog::qt_metacast(_clname);
}

int OvalObjectDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QInputDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_OvalObject[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   12,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OvalObject[] = {
    "OvalObject\0\0newName\0setName(QString)\0"
};

void OvalObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        OvalObject *_t = static_cast<OvalObject *>(_o);
        switch (_id) {
        case 0: _t->setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData OvalObject::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject OvalObject::staticMetaObject = {
    { &ObjectNode::staticMetaObject, qt_meta_stringdata_OvalObject,
      qt_meta_data_OvalObject, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OvalObject::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OvalObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OvalObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OvalObject))
        return static_cast<void*>(const_cast< OvalObject*>(this));
    return ObjectNode::qt_metacast(_clname);
}

int OvalObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ObjectNode::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
