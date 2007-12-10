/****************************************************************************
** Meta object code from reading C++ file 'ClientSocketList.h'
**
** Created: Fri Apr 21 16:18:59 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ClientSocketList.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClientSocketList.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_TestServer__ClientSocketList[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      29,   52,   52,   52, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_TestServer__ClientSocketList[] = {
    "TestServer::ClientSocketList\0loggingSignal(QString)\0\0"
};

const QMetaObject TestServer::ClientSocketList::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TestServer__ClientSocketList,
      qt_meta_data_TestServer__ClientSocketList, 0 }
};

const QMetaObject *TestServer::ClientSocketList::metaObject() const
{
    return &staticMetaObject;
}

void *TestServer::ClientSocketList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TestServer__ClientSocketList))
	return static_cast<void*>(const_cast<ClientSocketList*>(this));
    return QObject::qt_metacast(_clname);
}

int TestServer::ClientSocketList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loggingSignal(*reinterpret_cast< QString*>(_a[1])); break;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void TestServer::ClientSocketList::loggingSignal(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
