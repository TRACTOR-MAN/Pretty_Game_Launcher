/****************************************************************************
** Meta object code from reading C++ file 'game_data_gui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Gui/Include/game_data_gui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game_data_gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_gameNameButtonWidget_t {
    QByteArrayData data[6];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gameNameButtonWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gameNameButtonWidget_t qt_meta_stringdata_gameNameButtonWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "gameNameButtonWidget"
QT_MOC_LITERAL(1, 21, 14), // "nameBtnclicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 21), // "gameNameButtonWidget&"
QT_MOC_LITERAL(4, 59, 12), // "buttonWidget"
QT_MOC_LITERAL(5, 72, 13) // "buttonClicked"

    },
    "gameNameButtonWidget\0nameBtnclicked\0"
    "\0gameNameButtonWidget&\0buttonWidget\0"
    "buttonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gameNameButtonWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void gameNameButtonWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<gameNameButtonWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nameBtnclicked((*reinterpret_cast< gameNameButtonWidget(*)>(_a[1]))); break;
        case 1: _t->buttonClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (gameNameButtonWidget::*)(gameNameButtonWidget & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gameNameButtonWidget::nameBtnclicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject gameNameButtonWidget::staticMetaObject = { {
    &QPushButton::staticMetaObject,
    qt_meta_stringdata_gameNameButtonWidget.data,
    qt_meta_data_gameNameButtonWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *gameNameButtonWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gameNameButtonWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_gameNameButtonWidget.stringdata0))
        return static_cast<void*>(this);
    return QPushButton::qt_metacast(_clname);
}

int gameNameButtonWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void gameNameButtonWidget::nameBtnclicked(gameNameButtonWidget & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_LaunchButtonWidget_t {
    QByteArrayData data[6];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LaunchButtonWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LaunchButtonWidget_t qt_meta_stringdata_LaunchButtonWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "LaunchButtonWidget"
QT_MOC_LITERAL(1, 19, 16), // "launchBtnClicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 19), // "LaunchButtonWidget&"
QT_MOC_LITERAL(4, 57, 12), // "launchWidget"
QT_MOC_LITERAL(5, 70, 10) // "launchGame"

    },
    "LaunchButtonWidget\0launchBtnClicked\0"
    "\0LaunchButtonWidget&\0launchWidget\0"
    "launchGame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LaunchButtonWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void LaunchButtonWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LaunchButtonWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->launchBtnClicked((*reinterpret_cast< LaunchButtonWidget(*)>(_a[1]))); break;
        case 1: _t->launchGame(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LaunchButtonWidget::*)(LaunchButtonWidget & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LaunchButtonWidget::launchBtnClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LaunchButtonWidget::staticMetaObject = { {
    &QPushButton::staticMetaObject,
    qt_meta_stringdata_LaunchButtonWidget.data,
    qt_meta_data_LaunchButtonWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LaunchButtonWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LaunchButtonWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LaunchButtonWidget.stringdata0))
        return static_cast<void*>(this);
    return QPushButton::qt_metacast(_clname);
}

int LaunchButtonWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void LaunchButtonWidget::launchBtnClicked(LaunchButtonWidget & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_gameTitleWidget_t {
    QByteArrayData data[6];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gameTitleWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gameTitleWidget_t qt_meta_stringdata_gameTitleWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "gameTitleWidget"
QT_MOC_LITERAL(1, 16, 23), // "updatePrettyInformation"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 21), // "gameNameButtonWidget&"
QT_MOC_LITERAL(4, 63, 12), // "buttonwidget"
QT_MOC_LITERAL(5, 76, 20) // "updatePrettyGameInfo"

    },
    "gameTitleWidget\0updatePrettyInformation\0"
    "\0gameNameButtonWidget&\0buttonwidget\0"
    "updatePrettyGameInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gameTitleWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void gameTitleWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<gameTitleWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updatePrettyInformation((*reinterpret_cast< gameNameButtonWidget(*)>(_a[1]))); break;
        case 1: _t->updatePrettyGameInfo((*reinterpret_cast< gameNameButtonWidget(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (gameTitleWidget::*)(gameNameButtonWidget & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gameTitleWidget::updatePrettyInformation)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject gameTitleWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_gameTitleWidget.data,
    qt_meta_data_gameTitleWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *gameTitleWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gameTitleWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_gameTitleWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int gameTitleWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void gameTitleWidget::updatePrettyInformation(gameNameButtonWidget & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_gamePrettyWidget_t {
    QByteArrayData data[1];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gamePrettyWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gamePrettyWidget_t qt_meta_stringdata_gamePrettyWidget = {
    {
QT_MOC_LITERAL(0, 0, 16) // "gamePrettyWidget"

    },
    "gamePrettyWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gamePrettyWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void gamePrettyWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject gamePrettyWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_gamePrettyWidget.data,
    qt_meta_data_gamePrettyWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *gamePrettyWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gamePrettyWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_gamePrettyWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int gamePrettyWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_gameDataGuiWidget_t {
    QByteArrayData data[5];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gameDataGuiWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gameDataGuiWidget_t qt_meta_stringdata_gameDataGuiWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "gameDataGuiWidget"
QT_MOC_LITERAL(1, 18, 23), // "redrawPrettyInformation"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 21), // "gameNameButtonWidget&"
QT_MOC_LITERAL(4, 65, 17) // "buttonInformation"

    },
    "gameDataGuiWidget\0redrawPrettyInformation\0"
    "\0gameNameButtonWidget&\0buttonInformation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gameDataGuiWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void gameDataGuiWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<gameDataGuiWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->redrawPrettyInformation((*reinterpret_cast< gameNameButtonWidget(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject gameDataGuiWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_gameDataGuiWidget.data,
    qt_meta_data_gameDataGuiWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *gameDataGuiWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gameDataGuiWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_gameDataGuiWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int gameDataGuiWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
