/****************************************************************************
** Meta object code from reading C++ file 'canvas.h'
**
** Created: Thu Mar 1 15:17:28 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/canvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Canvas[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,    8,    7,    7, 0x05,
      44,    8,    7,    7, 0x05,
      71,    8,    7,    7, 0x05,
      92,    8,    7,    7, 0x05,
     123,    8,    7,    7, 0x05,
     162,  154,    7,    7, 0x05,
     180,    7,    7,    7, 0x05,
     203,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     218,    7,    7,    7, 0x0a,
     246,    7,    7,    7, 0x0a,
     271,    7,    7,    7, 0x0a,
     297,    7,    7,    7, 0x0a,
     324,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Canvas[] = {
    "Canvas\0\0point\0objectSelectionChange(QPoint)\0"
    "moveSelectedObject(QPoint)\0"
    "createObject(QPoint)\0"
    "createConnectionPoint1(QPoint)\0"
    "createConnectionPoint2(QPoint)\0painter\0"
    "redraw(QPainter&)\0showPropertiesDialog()\0"
    "removeObject()\0on_actionDelete_triggered()\0"
    "on_actionCut_triggered()\0"
    "on_actionCopy_triggered()\0"
    "on_actionPaste_triggered()\0"
    "on_actionProperties_triggered()\0"
};

void Canvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Canvas *_t = static_cast<Canvas *>(_o);
        switch (_id) {
        case 0: _t->objectSelectionChange((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->moveSelectedObject((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 2: _t->createObject((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 3: _t->createConnectionPoint1((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 4: _t->createConnectionPoint2((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 5: _t->redraw((*reinterpret_cast< QPainter(*)>(_a[1]))); break;
        case 6: _t->showPropertiesDialog(); break;
        case 7: _t->removeObject(); break;
        case 8: _t->on_actionDelete_triggered(); break;
        case 9: _t->on_actionCut_triggered(); break;
        case 10: _t->on_actionCopy_triggered(); break;
        case 11: _t->on_actionPaste_triggered(); break;
        case 12: _t->on_actionProperties_triggered(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Canvas::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Canvas::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Canvas,
      qt_meta_data_Canvas, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Canvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Canvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Canvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Canvas))
        return static_cast<void*>(const_cast< Canvas*>(this));
    return QWidget::qt_metacast(_clname);
}

int Canvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Canvas::objectSelectionChange(const QPoint & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Canvas::moveSelectedObject(const QPoint & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Canvas::createObject(const QPoint & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Canvas::createConnectionPoint1(const QPoint & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Canvas::createConnectionPoint2(const QPoint & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Canvas::redraw(QPainter & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Canvas::showPropertiesDialog()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void Canvas::removeObject()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}
QT_END_MOC_NAMESPACE
