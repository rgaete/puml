/****************************************************************************
** Meta object code from reading C++ file 'nodeaction.h'
**
** Created: Thu Feb 16 18:42:49 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "nodeaction.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nodeaction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NodeAction[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      64,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NodeAction[] = {
    "NodeAction\0\0mode,prototypeID\0"
    "triggered(Canvas::DrawingMode,int)\0"
    "onTriggered()\0"
};

const QMetaObject NodeAction::staticMetaObject = {
    { &QAction::staticMetaObject, qt_meta_stringdata_NodeAction,
      qt_meta_data_NodeAction, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NodeAction::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NodeAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NodeAction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NodeAction))
        return static_cast<void*>(const_cast< NodeAction*>(this));
    return QAction::qt_metacast(_clname);
}

int NodeAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAction::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: triggered((*reinterpret_cast< Canvas::DrawingMode(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: onTriggered(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void NodeAction::triggered(Canvas::DrawingMode _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE