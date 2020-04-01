/****************************************************************************
** Meta object code from reading C++ file 'Enki.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Enki.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Enki.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Enki__EnkiWidget_t {
    QByteArrayData data[21];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Enki__EnkiWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Enki__EnkiWidget_t qt_meta_stringdata_Enki__EnkiWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "Enki::EnkiWidget"
QT_MOC_LITERAL(1, 17, 9), // "setCamera"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 3), // "pos"
QT_MOC_LITERAL(4, 32, 8), // "altitude"
QT_MOC_LITERAL(5, 41, 3), // "yaw"
QT_MOC_LITERAL(6, 45, 5), // "pitch"
QT_MOC_LITERAL(7, 51, 1), // "x"
QT_MOC_LITERAL(8, 53, 1), // "y"
QT_MOC_LITERAL(9, 55, 17), // "restartDumpFrames"
QT_MOC_LITERAL(10, 73, 13), // "setDumpFrames"
QT_MOC_LITERAL(11, 87, 6), // "doDump"
QT_MOC_LITERAL(12, 94, 11), // "setTracking"
QT_MOC_LITERAL(13, 106, 7), // "doTrack"
QT_MOC_LITERAL(14, 114, 14), // "toggleTracking"
QT_MOC_LITERAL(15, 129, 14), // "addInfoMessage"
QT_MOC_LITERAL(16, 144, 7), // "message"
QT_MOC_LITERAL(17, 152, 11), // "persistance"
QT_MOC_LITERAL(18, 164, 5), // "color"
QT_MOC_LITERAL(19, 170, 4), // "link"
QT_MOC_LITERAL(20, 175, 8) // "showHelp"

    },
    "Enki::EnkiWidget\0setCamera\0\0pos\0"
    "altitude\0yaw\0pitch\0x\0y\0restartDumpFrames\0"
    "setDumpFrames\0doDump\0setTracking\0"
    "doTrack\0toggleTracking\0addInfoMessage\0"
    "message\0persistance\0color\0link\0showHelp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Enki__EnkiWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    4,   69,    2, 0x0a /* Public */,
       1,    5,   78,    2, 0x0a /* Public */,
       9,    0,   89,    2, 0x0a /* Public */,
      10,    1,   90,    2, 0x0a /* Public */,
      12,    1,   93,    2, 0x0a /* Public */,
      14,    0,   96,    2, 0x0a /* Public */,
      15,    4,   97,    2, 0x0a /* Public */,
      15,    3,  106,    2, 0x2a /* Public | MethodCloned */,
      15,    2,  113,    2, 0x2a /* Public | MethodCloned */,
      15,    1,  118,    2, 0x2a /* Public | MethodCloned */,
      20,    0,  121,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QPointF, QMetaType::Double, QMetaType::Double, QMetaType::Double,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    7,    8,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Double, QMetaType::QColor, QMetaType::QUrl,   16,   17,   18,   19,
    QMetaType::Void, QMetaType::QString, QMetaType::Double, QMetaType::QColor,   16,   17,   18,
    QMetaType::Void, QMetaType::QString, QMetaType::Double,   16,   17,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,

       0        // eod
};

void Enki::EnkiWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EnkiWidget *_t = static_cast<EnkiWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setCamera((*reinterpret_cast< const QPointF(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 1: _t->setCamera((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 2: _t->restartDumpFrames(); break;
        case 3: _t->setDumpFrames((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->setTracking((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->toggleTracking(); break;
        case 6: _t->addInfoMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< const QColor(*)>(_a[3])),(*reinterpret_cast< const QUrl(*)>(_a[4]))); break;
        case 7: _t->addInfoMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< const QColor(*)>(_a[3]))); break;
        case 8: _t->addInfoMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 9: _t->addInfoMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->showHelp(); break;
        default: ;
        }
    }
}

const QMetaObject Enki::EnkiWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_Enki__EnkiWidget.data,
      qt_meta_data_Enki__EnkiWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Enki::EnkiWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Enki::EnkiWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Enki__EnkiWidget.stringdata0))
        return static_cast<void*>(this);
    return QGLWidget::qt_metacast(_clname);
}

int Enki::EnkiWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
