/****************************************************************************
** Meta object code from reading C++ file 'kabinet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kabinet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kabinet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Kabinet_t {
    QByteArrayData data[17];
    char stringdata[321];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Kabinet_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Kabinet_t qt_meta_stringdata_Kabinet = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Kabinet"
QT_MOC_LITERAL(1, 8, 19), // "on_checkBox_clicked"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 7), // "checked"
QT_MOC_LITERAL(4, 37, 21), // "on_checkBox_2_clicked"
QT_MOC_LITERAL(5, 59, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(6, 81, 26), // "on_checkBox_5_stateChanged"
QT_MOC_LITERAL(7, 108, 4), // "arg1"
QT_MOC_LITERAL(8, 113, 26), // "on_checkBox_7_stateChanged"
QT_MOC_LITERAL(9, 140, 21), // "on_listWidget_clicked"
QT_MOC_LITERAL(10, 162, 5), // "index"
QT_MOC_LITERAL(11, 168, 23), // "on_listWidget_3_clicked"
QT_MOC_LITERAL(12, 192, 23), // "on_listWidget_2_clicked"
QT_MOC_LITERAL(13, 216, 32), // "on_pushButton_CreateRoom_clicked"
QT_MOC_LITERAL(14, 249, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(15, 273, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(16, 297, 23) // "on_listWidget_4_clicked"

    },
    "Kabinet\0on_checkBox_clicked\0\0checked\0"
    "on_checkBox_2_clicked\0on_pushButton_clicked\0"
    "on_checkBox_5_stateChanged\0arg1\0"
    "on_checkBox_7_stateChanged\0"
    "on_listWidget_clicked\0index\0"
    "on_listWidget_3_clicked\0on_listWidget_2_clicked\0"
    "on_pushButton_CreateRoom_clicked\0"
    "on_pushButton_4_clicked\0on_pushButton_2_clicked\0"
    "on_listWidget_4_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Kabinet[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x08 /* Private */,
       4,    1,   77,    2, 0x08 /* Private */,
       5,    0,   80,    2, 0x08 /* Private */,
       6,    1,   81,    2, 0x08 /* Private */,
       8,    1,   84,    2, 0x08 /* Private */,
       9,    1,   87,    2, 0x08 /* Private */,
      11,    1,   90,    2, 0x08 /* Private */,
      12,    1,   93,    2, 0x08 /* Private */,
      13,    0,   96,    2, 0x08 /* Private */,
      14,    0,   97,    2, 0x08 /* Private */,
      15,    0,   98,    2, 0x08 /* Private */,
      16,    1,   99,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QModelIndex,   10,
    QMetaType::Void, QMetaType::QModelIndex,   10,
    QMetaType::Void, QMetaType::QModelIndex,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   10,

       0        // eod
};

void Kabinet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Kabinet *_t = static_cast<Kabinet *>(_o);
        switch (_id) {
        case 0: _t->on_checkBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_checkBox_2_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_clicked(); break;
        case 3: _t->on_checkBox_5_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_checkBox_7_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_listWidget_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->on_listWidget_3_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 7: _t->on_listWidget_2_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: _t->on_pushButton_CreateRoom_clicked(); break;
        case 9: _t->on_pushButton_4_clicked(); break;
        case 10: _t->on_pushButton_2_clicked(); break;
        case 11: _t->on_listWidget_4_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Kabinet::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Kabinet.data,
      qt_meta_data_Kabinet,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Kabinet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Kabinet::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Kabinet.stringdata))
        return static_cast<void*>(const_cast< Kabinet*>(this));
    return QDialog::qt_metacast(_clname);
}

int Kabinet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
