/****************************************************************************
** Meta object code from reading C++ file 'controlpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../RemoteApptics/controlpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controlpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ControlPanel_t {
    QByteArrayData data[19];
    char stringdata0[392];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControlPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControlPanel_t qt_meta_stringdata_ControlPanel = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ControlPanel"
QT_MOC_LITERAL(1, 13, 20), // "setServo1SliderValue"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 20), // "setServo2SliderValue"
QT_MOC_LITERAL(4, 56, 18), // "setServo1LabelText"
QT_MOC_LITERAL(5, 75, 18), // "setServo2LabelText"
QT_MOC_LITERAL(6, 94, 21), // "servo1SliderSetEnable"
QT_MOC_LITERAL(7, 116, 21), // "servo2SliderSetEnable"
QT_MOC_LITERAL(8, 138, 24), // "increase1ButtonSetEnable"
QT_MOC_LITERAL(9, 163, 24), // "increase2ButtonSetEnable"
QT_MOC_LITERAL(10, 188, 24), // "decrease1ButtonSetEnable"
QT_MOC_LITERAL(11, 213, 24), // "decrease2ButtonSetEnable"
QT_MOC_LITERAL(12, 238, 20), // "rigthButtonSetEnable"
QT_MOC_LITERAL(13, 259, 19), // "leftButtonSetEnable"
QT_MOC_LITERAL(14, 279, 17), // "upButtonSetEnable"
QT_MOC_LITERAL(15, 297, 19), // "downButtonSetEnable"
QT_MOC_LITERAL(16, 317, 25), // "step1SpeedSliderSetEnable"
QT_MOC_LITERAL(17, 343, 25), // "step2SpeedSliderSetEnable"
QT_MOC_LITERAL(18, 369, 22) // "refreshButtonSetEnable"

    },
    "ControlPanel\0setServo1SliderValue\0\0"
    "setServo2SliderValue\0setServo1LabelText\0"
    "setServo2LabelText\0servo1SliderSetEnable\0"
    "servo2SliderSetEnable\0increase1ButtonSetEnable\0"
    "increase2ButtonSetEnable\0"
    "decrease1ButtonSetEnable\0"
    "decrease2ButtonSetEnable\0rigthButtonSetEnable\0"
    "leftButtonSetEnable\0upButtonSetEnable\0"
    "downButtonSetEnable\0step1SpeedSliderSetEnable\0"
    "step2SpeedSliderSetEnable\0"
    "refreshButtonSetEnable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControlPanel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      17,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       3,    1,  102,    2, 0x06 /* Public */,
       4,    1,  105,    2, 0x06 /* Public */,
       5,    1,  108,    2, 0x06 /* Public */,
       6,    1,  111,    2, 0x06 /* Public */,
       7,    1,  114,    2, 0x06 /* Public */,
       8,    1,  117,    2, 0x06 /* Public */,
       9,    1,  120,    2, 0x06 /* Public */,
      10,    1,  123,    2, 0x06 /* Public */,
      11,    1,  126,    2, 0x06 /* Public */,
      12,    1,  129,    2, 0x06 /* Public */,
      13,    1,  132,    2, 0x06 /* Public */,
      14,    1,  135,    2, 0x06 /* Public */,
      15,    1,  138,    2, 0x06 /* Public */,
      16,    1,  141,    2, 0x06 /* Public */,
      17,    1,  144,    2, 0x06 /* Public */,
      18,    1,  147,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void ControlPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ControlPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setServo1SliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setServo2SliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setServo1LabelText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->setServo2LabelText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->servo1SliderSetEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->servo2SliderSetEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->increase1ButtonSetEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->increase2ButtonSetEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->decrease1ButtonSetEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->decrease2ButtonSetEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->rigthButtonSetEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->leftButtonSetEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->upButtonSetEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->downButtonSetEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->step1SpeedSliderSetEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->step2SpeedSliderSetEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->refreshButtonSetEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ControlPanel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::setServo1SliderValue)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::setServo2SliderValue)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::setServo1LabelText)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::setServo2LabelText)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::servo1SliderSetEnable)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::servo2SliderSetEnable)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::increase1ButtonSetEnable)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::increase2ButtonSetEnable)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::decrease1ButtonSetEnable)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::decrease2ButtonSetEnable)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::rigthButtonSetEnable)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::leftButtonSetEnable)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::upButtonSetEnable)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::downButtonSetEnable)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::step1SpeedSliderSetEnable)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::step2SpeedSliderSetEnable)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::refreshButtonSetEnable)) {
                *result = 16;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ControlPanel::staticMetaObject = { {
    QMetaObject::SuperData::link<ControlWindow::staticMetaObject>(),
    qt_meta_stringdata_ControlPanel.data,
    qt_meta_data_ControlPanel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ControlPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControlPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ControlPanel.stringdata0))
        return static_cast<void*>(this);
    return ControlWindow::qt_metacast(_clname);
}

int ControlPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ControlWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void ControlPanel::setServo1SliderValue(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ControlPanel::setServo2SliderValue(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ControlPanel::setServo1LabelText(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ControlPanel::setServo2LabelText(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ControlPanel::servo1SliderSetEnable(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ControlPanel::servo2SliderSetEnable(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ControlPanel::increase1ButtonSetEnable(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ControlPanel::increase2ButtonSetEnable(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ControlPanel::decrease1ButtonSetEnable(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ControlPanel::decrease2ButtonSetEnable(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ControlPanel::rigthButtonSetEnable(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void ControlPanel::leftButtonSetEnable(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void ControlPanel::upButtonSetEnable(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void ControlPanel::downButtonSetEnable(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void ControlPanel::step1SpeedSliderSetEnable(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void ControlPanel::step2SpeedSliderSetEnable(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void ControlPanel::refreshButtonSetEnable(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
