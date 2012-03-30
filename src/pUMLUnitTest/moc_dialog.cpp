/****************************************************************************
** Meta object code from reading C++ file 'dialog.h'
**
** Created: Thu Mar 29 18:29:13 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ConfigDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   14,   13,   13, 0x05,
      73,   64,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     115,   98,   13,   13, 0x0a,
     161,   13,   13,   13, 0x0a,
     177,   13,   13,   13, 0x0a,
     186,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ConfigDialog[] = {
    "ConfigDialog\0\0diagramType\0"
    "newDiagramType(BaseNode::DiagramType)\0"
    "filename\0openDiagramFile(QString)\0"
    "current,previous\0"
    "changePage(QListWidgetItem*,QListWidgetItem*)\0"
    "browseForFile()\0accept()\0reject()\0"
};

const QMetaObject ConfigDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ConfigDialog,
      qt_meta_data_ConfigDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConfigDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConfigDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConfigDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigDialog))
        return static_cast<void*>(const_cast< ConfigDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ConfigDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newDiagramType((*reinterpret_cast< BaseNode::DiagramType(*)>(_a[1]))); break;
        case 1: openDiagramFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: changePage((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        case 3: browseForFile(); break;
        case 4: accept(); break;
        case 5: reject(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ConfigDialog::newDiagramType(BaseNode::DiagramType _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConfigDialog::openDiagramFile(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
