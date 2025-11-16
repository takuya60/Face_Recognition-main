/****************************************************************************
** Meta object code from reading C++ file 'FaceWorker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "inc/FaceWorker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FaceWorker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FaceWorker_t {
    QByteArrayData data[22];
    char stringdata0[274];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FaceWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FaceWorker_t qt_meta_stringdata_FaceWorker = {
    {
QT_MOC_LITERAL(0, 0, 10), // "FaceWorker"
QT_MOC_LITERAL(1, 11, 10), // "frameReady"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 5), // "frame"
QT_MOC_LITERAL(4, 29, 13), // "snapshotReady"
QT_MOC_LITERAL(5, 43, 8), // "snapshot"
QT_MOC_LITERAL(6, 52, 13), // "statusChanged"
QT_MOC_LITERAL(7, 66, 7), // "message"
QT_MOC_LITERAL(8, 74, 13), // "idStatusReady"
QT_MOC_LITERAL(9, 88, 11), // "isAvailable"
QT_MOC_LITERAL(10, 100, 22), // "recognitionResultReady"
QT_MOC_LITERAL(11, 123, 17), // "RecognitionResult"
QT_MOC_LITERAL(12, 141, 6), // "result"
QT_MOC_LITERAL(13, 148, 15), // "startProcessing"
QT_MOC_LITERAL(14, 164, 8), // "deviceId"
QT_MOC_LITERAL(15, 173, 14), // "stopProcessing"
QT_MOC_LITERAL(16, 188, 15), // "captureSnapshot"
QT_MOC_LITERAL(17, 204, 18), // "enrollCapturedFace"
QT_MOC_LITERAL(18, 223, 10), // "employeeId"
QT_MOC_LITERAL(19, 234, 12), // "employeeName"
QT_MOC_LITERAL(20, 247, 19), // "checkIdAvailability"
QT_MOC_LITERAL(21, 267, 6) // "id_str"

    },
    "FaceWorker\0frameReady\0\0frame\0snapshotReady\0"
    "snapshot\0statusChanged\0message\0"
    "idStatusReady\0isAvailable\0"
    "recognitionResultReady\0RecognitionResult\0"
    "result\0startProcessing\0deviceId\0"
    "stopProcessing\0captureSnapshot\0"
    "enrollCapturedFace\0employeeId\0"
    "employeeName\0checkIdAvailability\0"
    "id_str"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FaceWorker[] = {

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
       6,    1,   70,    2, 0x06 /* Public */,
       8,    1,   73,    2, 0x06 /* Public */,
      10,    1,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,   79,    2, 0x0a /* Public */,
      15,    0,   82,    2, 0x0a /* Public */,
      16,    0,   83,    2, 0x0a /* Public */,
      17,    2,   84,    2, 0x0a /* Public */,
      20,    1,   89,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, QMetaType::QImage,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, 0x80000000 | 11,   12,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   18,   19,
    QMetaType::Void, QMetaType::QString,   21,

       0        // eod
};

void FaceWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FaceWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->frameReady((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 1: _t->snapshotReady((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 2: _t->statusChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->idStatusReady((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->recognitionResultReady((*reinterpret_cast< const RecognitionResult(*)>(_a[1]))); break;
        case 5: _t->startProcessing((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->stopProcessing(); break;
        case 7: _t->captureSnapshot(); break;
        case 8: _t->enrollCapturedFace((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->checkIdAvailability((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
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
            using _t = void (FaceWorker::*)(const QImage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FaceWorker::frameReady)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FaceWorker::*)(const QImage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FaceWorker::snapshotReady)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FaceWorker::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FaceWorker::statusChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FaceWorker::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FaceWorker::idStatusReady)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FaceWorker::*)(const RecognitionResult & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FaceWorker::recognitionResultReady)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FaceWorker::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_FaceWorker.data,
    qt_meta_data_FaceWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FaceWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FaceWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FaceWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FaceWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void FaceWorker::frameReady(const QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FaceWorker::snapshotReady(const QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FaceWorker::statusChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FaceWorker::idStatusReady(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FaceWorker::recognitionResultReady(const RecognitionResult & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
