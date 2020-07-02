/****************************************************************************
** Meta object code from reading C++ file 'calibrationpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../RemoteApptics/calibrationpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calibrationpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CalibrationPanel_t {
    QByteArrayData data[12];
    char stringdata0[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CalibrationPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CalibrationPanel_t qt_meta_stringdata_CalibrationPanel = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CalibrationPanel"
QT_MOC_LITERAL(1, 17, 15), // "setStep1Current"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 15), // "setStep2Current"
QT_MOC_LITERAL(4, 50, 11), // "setStep1Max"
QT_MOC_LITERAL(5, 62, 11), // "setStep2Max"
QT_MOC_LITERAL(6, 74, 16), // "setServo1Current"
QT_MOC_LITERAL(7, 91, 16), // "setServo2Current"
QT_MOC_LITERAL(8, 108, 12), // "setServo1Top"
QT_MOC_LITERAL(9, 121, 12), // "setServo2Top"
QT_MOC_LITERAL(10, 134, 15), // "setServo1Bottom"
QT_MOC_LITERAL(11, 150, 15) // "setServo2Bottom"

    },
    "CalibrationPanel\0setStep1Current\0\0"
    "setStep2Current\0setStep1Max\0setStep2Max\0"
    "setServo1Current\0setServo2Current\0"
    "setServo1Top\0setServo2Top\0setServo1Bottom\0"
    "setServo2Bottom"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CalibrationPanel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       3,    1,   67,    2, 0x06 /* Public */,
       4,    1,   70,    2, 0x06 /* Public */,
       5,    1,   73,    2, 0x06 /* Public */,
       6,    1,   76,    2, 0x06 /* Public */,
       7,    1,   79,    2, 0x06 /* Public */,
       8,    1,   82,    2, 0x06 /* Public */,
       9,    1,   85,    2, 0x06 /* Public */,
      10,    1,   88,    2, 0x06 /* Public */,
      11,    1,   91,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void CalibrationPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CalibrationPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setStep1Current((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->setStep2Current((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->setStep1Max((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->setStep2Max((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->setServo1Current((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->setServo2Current((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->setServo1Top((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->setServo2Top((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->setServo1Bottom((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->setServo2Bottom((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CalibrationPanel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalibrationPanel::setStep1Current)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CalibrationPanel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalibrationPanel::setStep2Current)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CalibrationPanel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalibrationPanel::setStep1Max)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CalibrationPanel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalibrationPanel::setStep2Max)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CalibrationPanel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalibrationPanel::setServo1Current)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CalibrationPanel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalibrationPanel::setServo2Current)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (CalibrationPanel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalibrationPanel::setServo1Top)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (CalibrationPanel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalibrationPanel::setServo2Top)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (CalibrationPanel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalibrationPanel::setServo1Bottom)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (CalibrationPanel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalibrationPanel::setServo2Bottom)) {
                *result = 9;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CalibrationPanel::staticMetaObject = { {
    QMetaObject::SuperData::link<CalibrationWindow::staticMetaObject>(),
    qt_meta_stringdata_CalibrationPanel.data,
    qt_meta_data_CalibrationPanel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CalibrationPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CalibrationPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CalibrationPanel.stringdata0))
        return static_cast<void*>(this);
    return CalibrationWindow::qt_metacast(_clname);
}

int CalibrationPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CalibrationWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void CalibrationPanel::setStep1Current(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CalibrationPanel::setStep2Current(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CalibrationPanel::setStep1Max(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CalibrationPanel::setStep2Max(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CalibrationPanel::setServo1Current(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CalibrationPanel::setServo2Current(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CalibrationPanel::setServo1Top(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void CalibrationPanel::setServo2Top(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void CalibrationPanel::setServo1Bottom(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void CalibrationPanel::setServo2Bottom(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
