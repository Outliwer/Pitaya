/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[208];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 3), // "New"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 4), // "Open"
QT_MOC_LITERAL(4, 21, 4), // "Save"
QT_MOC_LITERAL(5, 26, 6), // "SaveAs"
QT_MOC_LITERAL(6, 33, 4), // "Undo"
QT_MOC_LITERAL(7, 38, 4), // "Redo"
QT_MOC_LITERAL(8, 43, 14), // "ProjectManager"
QT_MOC_LITERAL(9, 58, 9), // "StatusBar"
QT_MOC_LITERAL(10, 68, 11), // "Attribution"
QT_MOC_LITERAL(11, 80, 10), // "Cloudmodel"
QT_MOC_LITERAL(12, 91, 6), // "OSGimg"
QT_MOC_LITERAL(13, 98, 19), // "AerialTriangulation"
QT_MOC_LITERAL(14, 118, 8), // "Distance"
QT_MOC_LITERAL(15, 127, 7), // "Options"
QT_MOC_LITERAL(16, 135, 12), // "Panoramicimg"
QT_MOC_LITERAL(17, 148, 6), // "Report"
QT_MOC_LITERAL(18, 155, 14), // "DistanceReport"
QT_MOC_LITERAL(19, 170, 7), // "SeeHelp"
QT_MOC_LITERAL(20, 178, 12), // "SendFeedback"
QT_MOC_LITERAL(21, 191, 16) // "TechnicalSupport"

    },
    "MainWindow\0New\0\0Open\0Save\0SaveAs\0Undo\0"
    "Redo\0ProjectManager\0StatusBar\0Attribution\0"
    "Cloudmodel\0OSGimg\0AerialTriangulation\0"
    "Distance\0Options\0Panoramicimg\0Report\0"
    "DistanceReport\0SeeHelp\0SendFeedback\0"
    "TechnicalSupport"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x09 /* Protected */,
       3,    0,  115,    2, 0x09 /* Protected */,
       4,    0,  116,    2, 0x09 /* Protected */,
       5,    0,  117,    2, 0x09 /* Protected */,
       6,    0,  118,    2, 0x09 /* Protected */,
       7,    0,  119,    2, 0x09 /* Protected */,
       8,    0,  120,    2, 0x09 /* Protected */,
       9,    0,  121,    2, 0x09 /* Protected */,
      10,    0,  122,    2, 0x09 /* Protected */,
      11,    0,  123,    2, 0x09 /* Protected */,
      12,    0,  124,    2, 0x09 /* Protected */,
      13,    0,  125,    2, 0x09 /* Protected */,
      14,    0,  126,    2, 0x09 /* Protected */,
      15,    0,  127,    2, 0x09 /* Protected */,
      16,    0,  128,    2, 0x09 /* Protected */,
      17,    0,  129,    2, 0x09 /* Protected */,
      18,    0,  130,    2, 0x09 /* Protected */,
      19,    0,  131,    2, 0x09 /* Protected */,
      20,    0,  132,    2, 0x09 /* Protected */,
      21,    0,  133,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->New(); break;
        case 1: _t->Open(); break;
        case 2: _t->Save(); break;
        case 3: _t->SaveAs(); break;
        case 4: _t->Undo(); break;
        case 5: _t->Redo(); break;
        case 6: _t->ProjectManager(); break;
        case 7: _t->StatusBar(); break;
        case 8: _t->Attribution(); break;
        case 9: _t->Cloudmodel(); break;
        case 10: _t->OSGimg(); break;
        case 11: _t->AerialTriangulation(); break;
        case 12: _t->Distance(); break;
        case 13: _t->Options(); break;
        case 14: _t->Panoramicimg(); break;
        case 15: _t->Report(); break;
        case 16: _t->DistanceReport(); break;
        case 17: _t->SeeHelp(); break;
        case 18: _t->SendFeedback(); break;
        case 19: _t->TechnicalSupport(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
