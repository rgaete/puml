/****************************************************************************
** Meta object code from reading C++ file 'document.h'
**
** Created: Thu Mar 29 18:29:06 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../document.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'document.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Document[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   25,    9,    9, 0x0a,
      59,   53,    9,    9, 0x0a,
      85,   53,    9,    9, 0x0a,
     121,  112,    9,    9, 0x0a,
     142,   53,    9,    9, 0x0a,
     173,   53,    9,    9, 0x0a,
     204,    9,    9,    9, 0x0a,
     227,    9,    9,    9, 0x0a,
     242,    9,    9,    9, 0x0a,
     264,    9,    9,    9, 0x0a,
     286,    9,    9,    9, 0x0a,
     307,    9,    9,    9, 0x0a,
     336,  331,    9,    9, 0x0a,
     374,   53,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Document[] = {
    "Document\0\0modelChanged()\0painter\0"
    "drawList(QPainter&)\0point\0"
    "setSelectedObject(QPoint)\0"
    "moveSelectedObject(QPoint)\0position\0"
    "createObject(QPoint)\0"
    "createConnectionPoint1(QPoint)\0"
    "createConnectionPoint2(QPoint)\0"
    "showPropertiesDialog()\0removeObject()\0"
    "sendSelectedToFront()\0sendSelectedForward()\0"
    "sendSelectedToBack()\0sendSelectedBackwards()\0"
    "type\0setDiagramType(BaseNode::DiagramType)\0"
    "changeSecondConnectionPointHint(QPoint)\0"
};

const QMetaObject Document::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Document,
      qt_meta_data_Document, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Document::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Document::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Document::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Document))
        return static_cast<void*>(const_cast< Document*>(this));
    return QWidget::qt_metacast(_clname);
}

int Document::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: modelChanged(); break;
        case 1: drawList((*reinterpret_cast< QPainter(*)>(_a[1]))); break;
        case 2: setSelectedObject((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 3: moveSelectedObject((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 4: createObject((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 5: createConnectionPoint1((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 6: createConnectionPoint2((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 7: showPropertiesDialog(); break;
        case 8: removeObject(); break;
        case 9: sendSelectedToFront(); break;
        case 10: sendSelectedForward(); break;
        case 11: sendSelectedToBack(); break;
        case 12: sendSelectedBackwards(); break;
        case 13: setDiagramType((*reinterpret_cast< BaseNode::DiagramType(*)>(_a[1]))); break;
        case 14: changeSecondConnectionPointHint((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Document::modelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
