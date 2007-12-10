/****************************************************************************
** Meta object code from reading C++ file 'NetworkThread.h'
**
** Created: Fri Apr 21 11:27:13 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "NetworkThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NetworkThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_TestServer__NetworkThread[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      26,   39,   39,   39, 0x05,
      40,   39,   39,   39, 0x05,
      55,   39,   39,   39, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_TestServer__NetworkThread[] = {
    "TestServer::NetworkThread\0testSignal()\0\0intSignal(int)\0"
    "newNetworkConnection(QString)\0"
};

const QMetaObject TestServer::NetworkThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TestServer__NetworkThread,
      qt_meta_data_TestServer__NetworkThread, 0 }
};

const QMetaObject *TestServer::NetworkThread::metaObject() const
{
    return &staticMetaObject;
}

void *TestServer::NetworkThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TestServer__NetworkThread))
	return static_cast<void*>(const_cast<NetworkThread*>(this));
    return QObject::qt_metacast(_clname);
}

int TestServer::NetworkThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: testSignal(); break;
        case 1: intSignal(*reinterpret_cast< int*>(_a[1])); break;
        case 2: newNetworkConnection(*reinterpret_cast< QString*>(_a[1])); break;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void TestServer::NetworkThread::testSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void TestServer::NetworkThread::intSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TestServer::NetworkThread::newNetworkConnection(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
