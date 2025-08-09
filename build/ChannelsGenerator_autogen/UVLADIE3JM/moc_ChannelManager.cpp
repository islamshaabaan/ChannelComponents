/****************************************************************************
** Meta object code from reading C++ file 'ChannelManager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ChannelManager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChannelManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN14ChannelManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto ChannelManager::qt_create_metaobjectdata<qt_meta_tag_ZN14ChannelManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ChannelManager",
        "parameterModelChanged",
        "",
        "channelsChanged",
        "loadFromFile",
        "path",
        "selectChannel",
        "index",
        "logInteraction",
        "paramName",
        "QVariant",
        "oldValue",
        "newValue",
        "jsTimestamp",
        "channelCount",
        "channelName",
        "parameterModel",
        "QAbstractListModel*"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'parameterModelChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'channelsChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'loadFromFile'
        QtMocHelpers::MethodData<bool(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 5 },
        }}),
        // Method 'selectChannel'
        QtMocHelpers::MethodData<void(int)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 7 },
        }}),
        // Method 'logInteraction'
        QtMocHelpers::MethodData<void(const QString &, const QVariant &, const QVariant &, qint64)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 }, { 0x80000000 | 10, 11 }, { 0x80000000 | 10, 12 }, { QMetaType::LongLong, 13 },
        }}),
        // Method 'channelCount'
        QtMocHelpers::MethodData<int() const>(14, 2, QMC::AccessPublic, QMetaType::Int),
        // Method 'channelName'
        QtMocHelpers::MethodData<QString(int) const>(15, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::Int, 7 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'parameterModel'
        QtMocHelpers::PropertyData<QAbstractListModel*>(16, 0x80000000 | 17, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ChannelManager, qt_meta_tag_ZN14ChannelManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ChannelManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ChannelManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ChannelManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14ChannelManagerE_t>.metaTypes,
    nullptr
} };

void ChannelManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ChannelManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->parameterModelChanged(); break;
        case 1: _t->channelsChanged(); break;
        case 2: { bool _r = _t->loadFromFile((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->selectChannel((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->logInteraction((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<qint64>>(_a[4]))); break;
        case 5: { int _r = _t->channelCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 6: { QString _r = _t->channelName((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ChannelManager::*)()>(_a, &ChannelManager::parameterModelChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ChannelManager::*)()>(_a, &ChannelManager::channelsChanged, 1))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractListModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QAbstractListModel**>(_v) = _t->parameterModel(); break;
        default: break;
        }
    }
}

const QMetaObject *ChannelManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChannelManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ChannelManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ChannelManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ChannelManager::parameterModelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ChannelManager::channelsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
