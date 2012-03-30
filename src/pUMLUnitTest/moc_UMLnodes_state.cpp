/****************************************************************************
** Meta object code from reading C++ file 'UMLnodes_state.h'
**
** Created: Thu Mar 29 18:29:23 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../UMLnodes_state.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UMLnodes_state.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StateObject[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   13,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_StateObject[] = {
    "StateObject\0\0newName\0setName(QString)\0"
};

const QMetaObject StateObject::staticMetaObject = {
    { &ObjectNode::staticMetaObject, qt_meta_stringdata_StateObject,
      qt_meta_data_StateObject, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StateObject::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StateObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StateObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StateObject))
        return static_cast<void*>(const_cast< StateObject*>(this));
    return ObjectNode::qt_metacast(_clname);
}

int StateObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ObjectNode::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_StateObjectDialog[] = {

 // content:
       5,       // revision
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

static const char qt_meta_stringdata_StateObjectDialog[] = {
    "StateObjectDialog\0"
};

const QMetaObject StateObjectDialog::staticMetaObject = {
    { &QInputDialog::staticMetaObject, qt_meta_stringdata_StateObjectDialog,
      qt_meta_data_StateObjectDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StateObjectDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StateObjectDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StateObjectDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StateObjectDialog))
        return static_cast<void*>(const_cast< StateObjectDialog*>(this));
    return QInputDialog::qt_metacast(_clname);
}

int StateObjectDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QInputDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_InitialStateObject[] = {

 // content:
       5,       // revision
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

static const char qt_meta_stringdata_InitialStateObject[] = {
    "InitialStateObject\0"
};

const QMetaObject InitialStateObject::staticMetaObject = {
    { &ObjectNode::staticMetaObject, qt_meta_stringdata_InitialStateObject,
      qt_meta_data_InitialStateObject, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InitialStateObject::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InitialStateObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InitialStateObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InitialStateObject))
        return static_cast<void*>(const_cast< InitialStateObject*>(this));
    return ObjectNode::qt_metacast(_clname);
}

int InitialStateObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ObjectNode::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_FinalStateObject[] = {

 // content:
       5,       // revision
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

static const char qt_meta_stringdata_FinalStateObject[] = {
    "FinalStateObject\0"
};

const QMetaObject FinalStateObject::staticMetaObject = {
    { &ObjectNode::staticMetaObject, qt_meta_stringdata_FinalStateObject,
      qt_meta_data_FinalStateObject, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FinalStateObject::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FinalStateObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FinalStateObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FinalStateObject))
        return static_cast<void*>(const_cast< FinalStateObject*>(this));
    return ObjectNode::qt_metacast(_clname);
}

int FinalStateObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ObjectNode::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
