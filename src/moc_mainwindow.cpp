/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Tue Feb 21 19:52:09 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
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
      20,   14, // methods
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
     316,   11,   11,   11, 0x0a,
     357,  352,   11,   11, 0x0a,
     398,  352,   11,   11, 0x0a,
     437,  352,   11,   11, 0x0a,
     468,   11,   11,   11, 0x0a,
     498,   11,   11,   11, 0x0a,
     525,   11,   11,   11, 0x0a,
     562,  553,   11,   11, 0x0a,
     619,  595,   11,   11, 0x0a,

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
    "on_actionSelect_All_triggered()\0"
    "on_actionInverse_Select_triggered()\0"
    "arg1\0on_actionTile_Horizontally_toggled(bool)\0"
    "on_actionTile_Vertically_toggled(bool)\0"
    "on_actionCascade_toggled(bool)\0"
    "on_actionDocument_triggered()\0"
    "on_actionAbout_triggered()\0"
    "on_actionSelect_triggered()\0newIndex\0"
    "on_tabWidget_currentChanged(int)\0"
    "drawingMode,prototypeID\0"
    "on_NodeAction_triggered(Canvas::DrawingMode,int)\0"
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
        case 10: on_actionSelect_All_triggered(); break;
        case 11: on_actionInverse_Select_triggered(); break;
        case 12: on_actionTile_Horizontally_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: on_actionTile_Vertically_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: on_actionCascade_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: on_actionDocument_triggered(); break;
        case 16: on_actionAbout_triggered(); break;
        case 17: on_actionSelect_triggered(); break;
        case 18: on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: on_NodeAction_triggered((*reinterpret_cast< Canvas::DrawingMode(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
