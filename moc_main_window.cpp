/****************************************************************************
** Meta object code from reading C++ file 'main_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "inc/main_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Face_t {
    QByteArrayData data[25];
    char stringdata0[306];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Face_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Face_t qt_meta_stringdata_Face = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Face"
QT_MOC_LITERAL(1, 5, 17), // "read_notification"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 3), // "len"
QT_MOC_LITERAL(4, 28, 24), // "open_camera_notification"
QT_MOC_LITERAL(5, 53, 8), // "deviceId"
QT_MOC_LITERAL(6, 62, 24), // "stop_camera_notification"
QT_MOC_LITERAL(7, 87, 22), // "write_log_notification"
QT_MOC_LITERAL(8, 110, 8), // "log_info"
QT_MOC_LITERAL(9, 119, 3), // "log"
QT_MOC_LITERAL(10, 123, 28), // "enroll_new_face_notification"
QT_MOC_LITERAL(11, 152, 10), // "employeeID"
QT_MOC_LITERAL(12, 163, 12), // "employeeName"
QT_MOC_LITERAL(13, 176, 8), // "showLogs"
QT_MOC_LITERAL(14, 185, 17), // "QVector<log_info>"
QT_MOC_LITERAL(15, 203, 4), // "logs"
QT_MOC_LITERAL(16, 208, 9), // "showImage"
QT_MOC_LITERAL(17, 218, 5), // "frame"
QT_MOC_LITERAL(18, 224, 11), // "showMessage"
QT_MOC_LITERAL(19, 236, 7), // "message"
QT_MOC_LITERAL(20, 244, 8), // "facePass"
QT_MOC_LITERAL(21, 253, 17), // "RecognitionResult"
QT_MOC_LITERAL(22, 271, 6), // "result"
QT_MOC_LITERAL(23, 278, 18), // "showSnapshotWidget"
QT_MOC_LITERAL(24, 297, 8) // "shapshot"

    },
    "Face\0read_notification\0\0len\0"
    "open_camera_notification\0deviceId\0"
    "stop_camera_notification\0"
    "write_log_notification\0log_info\0log\0"
    "enroll_new_face_notification\0employeeID\0"
    "employeeName\0showLogs\0QVector<log_info>\0"
    "logs\0showImage\0frame\0showMessage\0"
    "message\0facePass\0RecognitionResult\0"
    "result\0showSnapshotWidget\0shapshot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Face[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       6,    0,   70,    2, 0x06 /* Public */,
       7,    1,   71,    2, 0x06 /* Public */,
      10,    2,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,   79,    2, 0x08 /* Private */,
      16,    1,   82,    2, 0x08 /* Private */,
      18,    1,   85,    2, 0x08 /* Private */,
      20,    1,   88,    2, 0x08 /* Private */,
      23,    1,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   11,   12,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::QImage,   17,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, QMetaType::QImage,   24,

       0        // eod
};

void Face::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Face *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->read_notification((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->open_camera_notification((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->stop_camera_notification(); break;
        case 3: _t->write_log_notification((*reinterpret_cast< const log_info(*)>(_a[1]))); break;
        case 4: _t->enroll_new_face_notification((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->showLogs((*reinterpret_cast< QVector<log_info>(*)>(_a[1]))); break;
        case 6: _t->showImage((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 7: _t->showMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->facePass((*reinterpret_cast< const RecognitionResult(*)>(_a[1]))); break;
        case 9: _t->showSnapshotWidget((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< RecognitionResult >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Face::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Face::read_notification)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Face::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Face::open_camera_notification)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Face::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Face::stop_camera_notification)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Face::*)(const log_info & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Face::write_log_notification)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Face::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Face::enroll_new_face_notification)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Face::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_Face.data,
    qt_meta_data_Face,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Face::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Face::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Face.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Face::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Face::read_notification(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Face::open_camera_notification(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Face::stop_camera_notification()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Face::write_log_notification(const log_info & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Face::enroll_new_face_notification(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
