/****************************************************************************
** Meta object code from reading C++ file 'QtWidgetsApplication1.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../QtWidgetsApplication1.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtWidgetsApplication1.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtWidgetsApplication1_t {
    QByteArrayData data[9];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtWidgetsApplication1_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtWidgetsApplication1_t qt_meta_stringdata_QtWidgetsApplication1 = {
    {
QT_MOC_LITERAL(0, 0, 21), // "QtWidgetsApplication1"
QT_MOC_LITERAL(1, 22, 11), // "btn1clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 11), // "btn2clicked"
QT_MOC_LITERAL(4, 47, 11), // "btn3clicked"
QT_MOC_LITERAL(5, 59, 11), // "btn4clicked"
QT_MOC_LITERAL(6, 71, 11), // "btn5clicked"
QT_MOC_LITERAL(7, 83, 10), // "show_video"
QT_MOC_LITERAL(8, 94, 11) // "btn7clicked"

    },
    "QtWidgetsApplication1\0btn1clicked\0\0"
    "btn2clicked\0btn3clicked\0btn4clicked\0"
    "btn5clicked\0show_video\0btn7clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtWidgetsApplication1[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QtWidgetsApplication1::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtWidgetsApplication1 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->btn1clicked(); break;
        case 1: _t->btn2clicked(); break;
        case 2: _t->btn3clicked(); break;
        case 3: _t->btn4clicked(); break;
        case 4: _t->btn5clicked(); break;
        case 5: _t->show_video(); break;
        case 6: _t->btn7clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject QtWidgetsApplication1::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_QtWidgetsApplication1.data,
    qt_meta_data_QtWidgetsApplication1,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QtWidgetsApplication1::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtWidgetsApplication1::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtWidgetsApplication1.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QtWidgetsApplication1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
