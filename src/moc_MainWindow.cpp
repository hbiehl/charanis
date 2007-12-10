/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created: Fri Apr 21 15:35:58 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_TestServer__MainWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      23,   41,   46,   46, 0x0a,
      47,   46,   46,   46, 0x0a,
      67,   46,   46,   46, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TestServer__MainWindow[] = {
    "TestServer::MainWindow\0writeLog(QString)\0text\0\0sendButtonClicked()\0"
    "intSlot(int)\0"
};

const QMetaObject TestServer::MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TestServer__MainWindow,
      qt_meta_data_TestServer__MainWindow, 0 }
};

const QMetaObject *TestServer::MainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *TestServer::MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TestServer__MainWindow))
	return static_cast<void*>(const_cast<MainWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int TestServer::MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: writeLog(*reinterpret_cast< QString*>(_a[1])); break;
        case 1: sendButtonClicked(); break;
        case 2: intSlot(*reinterpret_cast< int*>(_a[1])); break;
        }
        _id -= 3;
    }
    return _id;
}
