/****************************************************************************
** Meta object code from reading C++ file 'connectionpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../RemoteApptics/connectionpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connectionpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConnectionPanel_t {
    QByteArrayData data[10];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConnectionPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConnectionPanel_t qt_meta_stringdata_ConnectionPanel = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ConnectionPanel"
QT_MOC_LITERAL(1, 16, 12), // "setIpAddress"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 13), // "setStreamPort"
QT_MOC_LITERAL(4, 44, 14), // "setControlPort"
QT_MOC_LITERAL(5, 59, 20), // "hideConnectionWindow"
QT_MOC_LITERAL(6, 80, 13), // "hideButtonBox"
QT_MOC_LITERAL(7, 94, 14), // "showMessageBox"
QT_MOC_LITERAL(8, 109, 8), // "QWidget*"
QT_MOC_LITERAL(9, 118, 14) // "MessageBoxType"

    },
    "ConnectionPanel\0setIpAddress\0\0"
    "setStreamPort\0setControlPort\0"
    "hideConnectionWindow\0hideButtonBox\0"
    "showMessageBox\0QWidget*\0MessageBoxType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConnectionPanel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       3,    1,   47,    2, 0x06 /* Public */,
       4,    1,   50,    2, 0x06 /* Public */,
       5,    0,   53,    2, 0x06 /* Public */,
       6,    0,   54,    2, 0x06 /* Public */,
       7,    4,   55,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, 0x80000000 | 8, QMetaType::QString, QMetaType::QString, 0x80000000 | 9,    2,    2,    2,    2,

       0        // eod
};

void ConnectionPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConnectionPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setIpAddress((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->setStreamPort((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setControlPort((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->hideConnectionWindow(); break;
        case 4: _t->hideButtonBox(); break;
        case 5: { int _r = _t->showMessageBox((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< MessageBoxType(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
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
            using _t = void (ConnectionPanel::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionPanel::setIpAddress)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConnectionPanel::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionPanel::setStreamPort)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ConnectionPanel::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionPanel::setControlPort)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ConnectionPanel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionPanel::hideConnectionWindow)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ConnectionPanel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionPanel::hideButtonBox)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = int (ConnectionPanel::*)(QWidget * , QString , QString , MessageBoxType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionPanel::showMessageBox)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ConnectionPanel::staticMetaObject = { {
    QMetaObject::SuperData::link<ConnectionWindow::staticMetaObject>(),
    qt_meta_stringdata_ConnectionPanel.data,
    qt_meta_data_ConnectionPanel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConnectionPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConnectionPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectionPanel.stringdata0))
        return static_cast<void*>(this);
    return ConnectionWindow::qt_metacast(_clname);
}

int ConnectionPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ConnectionWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ConnectionPanel::setIpAddress(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConnectionPanel::setStreamPort(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ConnectionPanel::setControlPort(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ConnectionPanel::hideConnectionWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ConnectionPanel::hideButtonBox()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
int ConnectionPanel::showMessageBox(QWidget * _t1, QString _t2, QString _t3, MessageBoxType _t4)
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
    return _t0;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE