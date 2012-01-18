/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sat Jan 14 16:23:11 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QT Project/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      37,   11,   11,   11, 0x0a,
      63,   11,   11,   11, 0x0a,
      89,   11,   11,   11, 0x0a,
     118,   11,   11,   11, 0x0a,
     145,   11,   11,   11, 0x0a,
     180,   11,   11,   11, 0x0a,
     206,   11,   11,   11, 0x0a,
     232,   11,   11,   11, 0x0a,
     257,   11,   11,   11, 0x0a,
     284,   11,   11,   11, 0x0a,
     312,   11,   11,   11, 0x0a,
     344,   11,   11,   11, 0x0a,
     385,  380,   11,   11, 0x0a,
     415,  380,   11,   11, 0x0a,
     446,  380,   11,   11, 0x0a,
     479,  380,   11,   11, 0x0a,
     511,  380,   11,   11, 0x0a,
     540,  380,   11,   11, 0x0a,
     568,  380,   11,   11, 0x0a,
     603,  380,   11,   11, 0x0a,
     644,  380,   11,   11, 0x0a,
     683,  380,   11,   11, 0x0a,
     714,   11,   11,   11, 0x0a,
     744,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_actionNew_triggered()\0"
    "on_actionOpen_triggered()\0"
    "on_actionSave_triggered()\0"
    "on_actionSave_As_triggered()\0"
    "on_actionPrint_triggered()\0"
    "on_actionImport_Export_triggered()\0"
    "on_actionExit_triggered()\0"
    "on_actionCopy_triggered()\0"
    "on_actionCut_triggered()\0"
    "on_actionPaste_triggered()\0"
    "on_actionSelect_triggered()\0"
    "on_actionSelect_All_triggered()\0"
    "on_actionInverse_Select_triggered()\0"
    "arg1\0on_actionCircle_toggled(bool)\0"
    "on_actionDiamond_toggled(bool)\0"
    "on_actionRectangle_toggled(bool)\0"
    "on_actionStickMan_toggled(bool)\0"
    "on_actionArrow_toggled(bool)\0"
    "on_actionLine_toggled(bool)\0"
    "on_actionDotted_Line_toggled(bool)\0"
    "on_actionTile_Horizontally_toggled(bool)\0"
    "on_actionTile_Vertically_toggled(bool)\0"
    "on_actionCascade_toggled(bool)\0"
    "on_actionDocument_triggered()\0"
    "on_actionAbout_triggered()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_actionNew_triggered(); break;
        case 1: on_actionOpen_triggered(); break;
        case 2: on_actionSave_triggered(); break;
        case 3: on_actionSave_As_triggered(); break;
        case 4: on_actionPrint_triggered(); break;
        case 5: on_actionImport_Export_triggered(); break;
        case 6: on_actionExit_triggered(); break;
        case 7: on_actionCopy_triggered(); break;
        case 8: on_actionCut_triggered(); break;
        case 9: on_actionPaste_triggered(); break;
        case 10: on_actionSelect_triggered(); break;
        case 11: on_actionSelect_All_triggered(); break;
        case 12: on_actionInverse_Select_triggered(); break;
        case 13: on_actionCircle_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: on_actionDiamond_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: on_actionRectangle_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: on_actionStickMan_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: on_actionArrow_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: on_actionLine_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: on_actionDotted_Line_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: on_actionTile_Horizontally_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: on_actionTile_Vertically_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: on_actionCascade_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: on_actionDocument_triggered(); break;
        case 24: on_actionAbout_triggered(); break;
        default: ;
        }
        _id -= 25;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
