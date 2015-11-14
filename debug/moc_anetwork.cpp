/****************************************************************************
** Meta object code from reading C++ file 'anetwork.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../anetwork.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'anetwork.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ANetwork_t {
    QByteArrayData data[9];
    char stringdata[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ANetwork_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ANetwork_t qt_meta_stringdata_ANetwork = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ANetwork"
QT_MOC_LITERAL(1, 9, 8), // "ARequest"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 13), // "ANetworkReply"
QT_MOC_LITERAL(4, 33, 5), // "reply"
QT_MOC_LITERAL(5, 39, 12), // "FileFinished"
QT_MOC_LITERAL(6, 52, 4), // "text"
QT_MOC_LITERAL(7, 57, 16), // "getReplyFinished"
QT_MOC_LITERAL(8, 74, 14) // "QNetworkReply*"

    },
    "ANetwork\0ARequest\0\0ANetworkReply\0reply\0"
    "FileFinished\0text\0getReplyFinished\0"
    "QNetworkReply*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ANetwork[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       5,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    4,

       0        // eod
};

void ANetwork::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ANetwork *_t = static_cast<ANetwork *>(_o);
        switch (_id) {
        case 0: _t->ARequest((*reinterpret_cast< ANetworkReply(*)>(_a[1]))); break;
        case 1: _t->FileFinished((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->getReplyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ANetwork::*_t)(ANetworkReply );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ANetwork::ARequest)) {
                *result = 0;
            }
        }
        {
            typedef void (ANetwork::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ANetwork::FileFinished)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject ANetwork::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ANetwork.data,
      qt_meta_data_ANetwork,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ANetwork::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ANetwork::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ANetwork.stringdata))
        return static_cast<void*>(const_cast< ANetwork*>(this));
    return QObject::qt_metacast(_clname);
}

int ANetwork::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ANetwork::ARequest(ANetworkReply _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ANetwork::FileFinished(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
