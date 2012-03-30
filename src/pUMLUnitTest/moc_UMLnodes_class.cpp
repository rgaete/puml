/****************************************************************************
** Meta object code from reading C++ file 'UMLnodes_class.h'
**
** Created: Thu Mar 29 18:29:19 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../UMLnodes_class.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UMLnodes_class.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClassBoxObjectDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      35,   22,   21,   21, 0x05,
      71,   57,   21,   21, 0x05,
     105,   94,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
     125,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClassBoxObjectDialog[] = {
    "ClassBoxObjectDialog\0\0newClassName\0"
    "classNameSet(QString)\0newAttributes\0"
    "attributesSet(QString)\0newMethods\0"
    "methodsSet(QString)\0okButtonClicked()\0"
};

const QMetaObject ClassBoxObjectDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ClassBoxObjectDialog,
      qt_meta_data_ClassBoxObjectDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClassBoxObjectDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClassBoxObjectDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClassBoxObjectDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClassBoxObjectDialog))
        return static_cast<void*>(const_cast< ClassBoxObjectDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ClassBoxObjectDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: classNameSet((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: attributesSet((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: methodsSet((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: okButtonClicked(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ClassBoxObjectDialog::classNameSet(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClassBoxObjectDialog::attributesSet(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ClassBoxObjectDialog::methodsSet(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
static const uint qt_meta_data_ClassBoxObject[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   16,   15,   15, 0x0a,
      65,   51,   15,   15, 0x0a,
      99,   88,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ClassBoxObject[] = {
    "ClassBoxObject\0\0newClassName\0"
    "setClassName(QString)\0newAttributes\0"
    "setAttributes(QString)\0newMethods\0"
    "setMethods(QString)\0"
};

const QMetaObject ClassBoxObject::staticMetaObject = {
    { &ObjectNode::staticMetaObject, qt_meta_stringdata_ClassBoxObject,
      qt_meta_data_ClassBoxObject, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClassBoxObject::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClassBoxObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClassBoxObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClassBoxObject))
        return static_cast<void*>(const_cast< ClassBoxObject*>(this));
    return ObjectNode::qt_metacast(_clname);
}

int ClassBoxObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ObjectNode::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setClassName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: setAttributes((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: setMethods((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
