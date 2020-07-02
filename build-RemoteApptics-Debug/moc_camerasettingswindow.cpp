/****************************************************************************
** Meta object code from reading C++ file 'camerasettingswindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../RemoteApptics/camerasettingswindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camerasettingswindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CameraSettingsWindow_t {
    QByteArrayData data[17];
    char stringdata0[332];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CameraSettingsWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CameraSettingsWindow_t qt_meta_stringdata_CameraSettingsWindow = {
    {
QT_MOC_LITERAL(0, 0, 20), // "CameraSettingsWindow"
QT_MOC_LITERAL(1, 21, 22), // "cameraSettingsAccepted"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 22), // "brighnessSliderChanged"
QT_MOC_LITERAL(4, 68, 5), // "Value"
QT_MOC_LITERAL(5, 74, 21), // "contrastSliderChanged"
QT_MOC_LITERAL(6, 96, 23), // "saturationSliderChanged"
QT_MOC_LITERAL(7, 120, 16), // "hueSliderChanged"
QT_MOC_LITERAL(8, 137, 21), // "exposureSliderChanged"
QT_MOC_LITERAL(9, 159, 21), // "autoExposureTriggered"
QT_MOC_LITERAL(10, 181, 17), // "gainSliderChanged"
QT_MOC_LITERAL(11, 199, 17), // "autoGainTriggered"
QT_MOC_LITERAL(12, 217, 23), // "horizontalFlipTriggered"
QT_MOC_LITERAL(13, 241, 21), // "verticalFlipTriggered"
QT_MOC_LITERAL(14, 263, 27), // "powerFrequencySliderChanged"
QT_MOC_LITERAL(15, 291, 22), // "sharpnessSliderChanged"
QT_MOC_LITERAL(16, 314, 17) // "zoomSliderChanged"

    },
    "CameraSettingsWindow\0cameraSettingsAccepted\0"
    "\0brighnessSliderChanged\0Value\0"
    "contrastSliderChanged\0saturationSliderChanged\0"
    "hueSliderChanged\0exposureSliderChanged\0"
    "autoExposureTriggered\0gainSliderChanged\0"
    "autoGainTriggered\0horizontalFlipTriggered\0"
    "verticalFlipTriggered\0powerFrequencySliderChanged\0"
    "sharpnessSliderChanged\0zoomSliderChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraSettingsWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    1,   85,    2, 0x08 /* Private */,
       5,    1,   88,    2, 0x08 /* Private */,
       6,    1,   91,    2, 0x08 /* Private */,
       7,    1,   94,    2, 0x08 /* Private */,
       8,    1,   97,    2, 0x08 /* Private */,
       9,    1,  100,    2, 0x08 /* Private */,
      10,    1,  103,    2, 0x08 /* Private */,
      11,    1,  106,    2, 0x08 /* Private */,
      12,    1,  109,    2, 0x08 /* Private */,
      13,    1,  112,    2, 0x08 /* Private */,
      14,    1,  115,    2, 0x08 /* Private */,
      15,    1,  118,    2, 0x08 /* Private */,
      16,    1,  121,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,

       0        // eod
};

void CameraSettingsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CameraSettingsWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cameraSettingsAccepted(); break;
        case 1: _t->brighnessSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->contrastSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->saturationSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->hueSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->exposureSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->autoExposureTriggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->gainSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->autoGainTriggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->horizontalFlipTriggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->verticalFlipTriggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->powerFrequencySliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->sharpnessSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->zoomSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CameraSettingsWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<MainWindow::staticMetaObject>(),
    qt_meta_stringdata_CameraSettingsWindow.data,
    qt_meta_data_CameraSettingsWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CameraSettingsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraSettingsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CameraSettingsWindow.stringdata0))
        return static_cast<void*>(this);
    return MainWindow::qt_metacast(_clname);
}

int CameraSettingsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
