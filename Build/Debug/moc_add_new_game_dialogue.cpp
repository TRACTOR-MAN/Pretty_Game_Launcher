/****************************************************************************
** Meta object code from reading C++ file 'add_new_game_dialogue.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Gui/Include/add_new_game_dialogue.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'add_new_game_dialogue.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Add_New_Game_Dialogue_t {
    QByteArrayData data[10];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Add_New_Game_Dialogue_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Add_New_Game_Dialogue_t qt_meta_stringdata_Add_New_Game_Dialogue = {
    {
QT_MOC_LITERAL(0, 0, 21), // "Add_New_Game_Dialogue"
QT_MOC_LITERAL(1, 22, 23), // "launchScriptTextChanged"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 9), // "newString"
QT_MOC_LITERAL(4, 57, 19), // "gameIconTextChanged"
QT_MOC_LITERAL(5, 77, 21), // "searchForLaunchScript"
QT_MOC_LITERAL(6, 99, 17), // "searchForGameIcon"
QT_MOC_LITERAL(7, 117, 18), // "updateLaunchScript"
QT_MOC_LITERAL(8, 136, 12), // "selectedFile"
QT_MOC_LITERAL(9, 149, 14) // "updateGameIcon"

    },
    "Add_New_Game_Dialogue\0launchScriptTextChanged\0"
    "\0newString\0gameIconTextChanged\0"
    "searchForLaunchScript\0searchForGameIcon\0"
    "updateLaunchScript\0selectedFile\0"
    "updateGameIcon"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Add_New_Game_Dialogue[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   50,    2, 0x08 /* Private */,
       6,    0,   51,    2, 0x08 /* Private */,
       7,    1,   52,    2, 0x08 /* Private */,
       9,    1,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,

       0        // eod
};

void Add_New_Game_Dialogue::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Add_New_Game_Dialogue *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->launchScriptTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->gameIconTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->searchForLaunchScript(); break;
        case 3: _t->searchForGameIcon(); break;
        case 4: _t->updateLaunchScript((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->updateGameIcon((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Add_New_Game_Dialogue::*)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Add_New_Game_Dialogue::launchScriptTextChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Add_New_Game_Dialogue::*)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Add_New_Game_Dialogue::gameIconTextChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Add_New_Game_Dialogue::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_Add_New_Game_Dialogue.data,
    qt_meta_data_Add_New_Game_Dialogue,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Add_New_Game_Dialogue::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Add_New_Game_Dialogue::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Add_New_Game_Dialogue.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Add_New_Game_Dialogue::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Add_New_Game_Dialogue::launchScriptTextChanged(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Add_New_Game_Dialogue::gameIconTextChanged(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
