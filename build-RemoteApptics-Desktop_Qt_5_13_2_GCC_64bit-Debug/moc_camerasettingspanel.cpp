/****************************************************************************
** Meta object code from reading C++ file 'camerasettingspanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../RemoteApptics/camerasettingspanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camerasettingspanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CameraSettingsPanel_t {
    QByteArrayData data[16];
    char stringdata0[195];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CameraSettingsPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CameraSettingsPanel_t qt_meta_stringdata_CameraSettingsPanel = {
    {
QT_MOC_LITERAL(0, 0, 19), // "CameraSettingsPanel"
QT_MOC_LITERAL(1, 20, 13), // "setBrightness"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "Value"
QT_MOC_LITERAL(4, 41, 11), // "setContrast"
QT_MOC_LITERAL(5, 53, 13), // "setSaturation"
QT_MOC_LITERAL(6, 67, 6), // "setHue"
QT_MOC_LITERAL(7, 74, 11), // "setExposure"
QT_MOC_LITERAL(8, 86, 15), // "setAutoExposure"
QT_MOC_LITERAL(9, 102, 7), // "setGain"
QT_MOC_LITERAL(10, 110, 11), // "setAutoGain"
QT_MOC_LITERAL(11, 122, 17), // "setHorizontalFlip"
QT_MOC_LITERAL(12, 140, 15), // "setVerticalFlip"
QT_MOC_LITERAL(13, 156, 17), // "setPowerFrequency"
QT_MOC_LITERAL(14, 174, 12), // "setSharpness"
QT_MOC_LITERAL(15, 187, 7) // "setZoom"

    },
    "CameraSettingsPanel\0setBrightness\0\0"
    "Value\0setContrast\0setSaturation\0setHue\0"
    "setExposure\0setAutoExposure\0setGain\0"
    "setAutoGain\0setHorizontalFlip\0"
    "setVerticalFlip\0setPowerFrequency\0"
    "setSharpness\0setZoom"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraSettingsPanel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       5,    1,   85,    2, 0x06 /* Public */,
       6,    1,   88,    2, 0x06 /* Public */,
       7,    1,   91,    2, 0x06 /* Public */,
       8,    1,   94,    2, 0x06 /* Public */,
       9,    1,   97,    2, 0x06 /* Public */,
      10,    1,  100,    2, 0x06 /* Public */,
      11,    1,  103,    2, 0x06 /* Public */,
      12,    1,  106,    2, 0x06 /* Public */,
      13,    1,  109,    2, 0x06 /* Public */,
      14,    1,  112,    2, 0x06 /* Public */,
      15,    1,  115,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void CameraSettingsPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CameraSettingsPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setBrightness((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setContrast((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setSaturation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setHue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setExposure((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setAutoExposure((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setGain((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setAutoGain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->setHorizontalFlip((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->setVerticalFlip((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->setPowerFrequency((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->setSharpness((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->setZoom((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CameraSettingsPanel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraSettingsPanel::setBrightness)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CameraSettingsPanel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraSettingsPanel::setContrast)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CameraSettingsPanel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraSettingsPanel::setSaturation)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CameraSettingsPanel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraSettingsPanel::setHue)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CameraSettingsPanel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraSettingsPanel::setExposure)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CameraSettingsPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraSettingsPanel::setAutoExposure)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (CameraSettingsPanel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraSettingsPanel::setGain)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (CameraSettingsPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraSettingsPanel::setAutoGain)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (CameraSettingsPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraSettingsPanel::setHorizontalFlip)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (CameraSettingsPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraSettingsPanel::setVerticalFlip)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (CameraSettingsPanel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraSettingsPanel::setPowerFrequency)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (CameraSettingsPanel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraSettingsPanel::setSharpness)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (CameraSettingsPanel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraSettingsPanel::setZoom)) {
                *result = 12;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CameraSettingsPanel::staticMetaObject = { {
    &CameraSettingsWindow::staticMetaObject,
    qt_meta_stringdata_CameraSettingsPanel.data,
    qt_meta_data_CameraSettingsPanel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CameraSettingsPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraSettingsPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CameraSettingsPanel.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "SocketListener"))
        return static_cast< SocketListener*>(this);
    return CameraSettingsWindow::qt_metacast(_clname);
}

int CameraSettingsPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CameraSettingsWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void CameraSettingsPanel::setBrightness(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CameraSettingsPanel::setContrast(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CameraSettingsPanel::setSaturation(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CameraSettingsPanel::setHue(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CameraSettingsPanel::setExposure(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CameraSettingsPanel::setAutoExposure(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CameraSettingsPanel::setGain(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void CameraSettingsPanel::setAutoGain(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void CameraSettingsPanel::setHorizontalFlip(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void CameraSettingsPanel::setVerticalFlip(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void CameraSettingsPanel::setPowerFrequency(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void CameraSettingsPanel::setSharpness(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void CameraSettingsPanel::setZoom(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
