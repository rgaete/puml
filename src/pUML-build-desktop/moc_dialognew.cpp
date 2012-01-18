/****************************************************************************
** Meta object code from reading C++ file 'dialognew.h'
**
** Created: Sat Jan 14 16:23:12 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QT Project/dialognew.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialognew.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogNew[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      34,   10,   10,   10, 0x0a,
      66,   10,   10,   10, 0x0a,
      96,   10,   10,   10, 0x0a,
     129,   10,   10,   10, 0x0a,
     165,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DialogNew[] = {
    "DialogNew\0\0on_OkButton_accepted()\0"
    "on_UseCaseRadioButton_clicked()\0"
    "on_ClassRadioButton_clicked()\0"
    "on_ActivityRadioButton_clicked()\0"
    "on_InteractionRadioButton_clicked()\0"
    "on_StateRadioButton_clicked()\0"
};

const QMetaObject DialogNew::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogNew,
      qt_meta_data_DialogNew, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogNew::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogNew::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogNew::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogNew))
        return static_cast<void*>(const_cast< DialogNew*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogNew::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_OkButton_accepted(); break;
        case 1: on_UseCaseRadioButton_clicked(); break;
        case 2: on_ClassRadioButton_clicked(); break;
        case 3: on_ActivityRadioButton_clicked(); break;
        case 4: on_InteractionRadioButton_clicked(); break;
        case 5: on_StateRadioButton_clicked(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
