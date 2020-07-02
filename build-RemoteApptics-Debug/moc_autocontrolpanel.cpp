/****************************************************************************
** Meta object code from reading C++ file 'autocontrolpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../RemoteApptics/autocontrolpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'autocontrolpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AutoControlPanel_t {
    QByteArrayData data[9];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AutoControlPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AutoControlPanel_t qt_meta_stringdata_AutoControlPanel = {
    {
QT_MOC_LITERAL(0, 0, 16), // "AutoControlPanel"
QT_MOC_LITERAL(1, 17, 18), // "addButtonSetEnable"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 21), // "deleteButtonSetEnable"
QT_MOC_LITERAL(4, 59, 10), // "addCommand"
QT_MOC_LITERAL(5, 70, 11), // "markCommand"
QT_MOC_LITERAL(6, 82, 14), // "showMessageBox"
QT_MOC_LITERAL(7, 97, 8), // "QWidget*"
QT_MOC_LITERAL(8, 106, 14) // "MessageBoxType"

    },
    "AutoControlPanel\0addButtonSetEnable\0"
    "\0deleteButtonSetEnable\0addCommand\0"
    "markCommand\0showMessageBox\0QWidget*\0"
    "MessageBoxType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AutoControlPanel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    1,   42,    2, 0x06 /* Public */,
       4,    1,   45,    2, 0x06 /* Public */,
       5,    1,   48,    2, 0x06 /* Public */,
       6,    4,   51,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Int, 0x80000000 | 7, QMetaType::QString, QMetaType::QString, 0x80000000 | 8,    2,    2,    2,    2,

       0        // eod
};

void AutoControlPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AutoControlPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addButtonSetEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->deleteButtonSetEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->addCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->markCommand((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: { int _r = _t->showMessageBox((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< MessageBoxType(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AutoControlPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AutoControlPanel::addButtonSetEnable)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AutoControlPanel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AutoControlPanel::deleteButtonSetEnable)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AutoControlPanel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AutoControlPanel::addCommand)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AutoControlPanel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AutoControlPanel::markCommand)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = int (AutoControlPanel::*)(QWidget * , QString , QString , MessageBoxType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AutoControlPanel::showMessageBox)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AutoControlPanel::staticMetaObject = { {
    QMetaObject::SuperData::link<AutoControlWindow::staticMetaObject>(),
    qt_meta_stringdata_AutoControlPanel.data,
    qt_meta_data_AutoControlPanel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AutoControlPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AutoControlPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AutoControlPanel.stringdata0))
        return static_cast<void*>(this);
    return AutoControlWindow::qt_metacast(_clname);
}

int AutoControlPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AutoControlWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void AutoControlPanel::addButtonSetEnable(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AutoControlPanel::deleteButtonSetEnable(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AutoControlPanel::addCommand(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AutoControlPanel::markCommand(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
int AutoControlPanel::showMessageBox(QWidget * _t1, QString _t2, QString _t3, MessageBoxType _t4)
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
    return _t0;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
