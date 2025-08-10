#include "ParameterModel.h"
#include <QDebug>
#include <QDateTime>

ParameterModel::ParameterModel(QObject* parent) : QAbstractListModel(parent) 
{
}

int ParameterModel::rowCount(const QModelIndex &parent) const 
{
    Q_UNUSED(parent)
    
    return mItems.count();
}

QVariant ParameterModel::data(const QModelIndex &index, int role) const 
{
    if (!index.isValid()) return {};
    int row = index.row();
    if (row < 0 || row >= mItems.size()) return {};

    Parameter* p = mItems.at(row);
    switch(role) {
    case NameRole: return p->getName();
    case KindRole: return p->getKind();
    case ValueRole: return p->getValue();
    case MinRole: return p->getMin();
    case MaxRole: return p->getMax();
    case IsDecimalRole: return p->isDecimal();
    case OptionsRole: return p->getOptions();
    case IsFixedRole: return p->isFixed();
    default: return {};
    }
}

QHash<int, QByteArray> ParameterModel::roleNames() const 
{
    QHash<int, QByteArray> r;
    r[NameRole] = "name";
    r[KindRole] = "kind";
    r[ValueRole] = "value";
    r[MinRole] = "min";
    r[MaxRole] = "max";
    r[IsDecimalRole] = "isDecimal";
    r[OptionsRole] = "options";
    r[IsFixedRole] = "isFixed";
    
    return r;
}

void ParameterModel::setParameters(const QList<Parameter *> &params) 
{
    beginResetModel();

    // disconnect old connections
    for (const auto &c : mConnections) {
        QObject::disconnect(c);
    }
    mConnections.clear();

    
    mItems = params;

    // connect to each parameter's valueChanged so model updates when C++ changes the parameter
    for (int i = 0; i < mItems.size(); ++i) {
        Parameter* p = mItems.at(i);
        // capture i by value
        QMetaObject::Connection conn = connect(p, &Parameter::valueChanged, this,
            [this, i](const QVariant &oldValue, const QVariant &newValue) {
                QModelIndex idx = index(i);
                emit dataChanged(idx, idx, { ValueRole });
            });
        mConnections.append(conn);
    }

    endResetModel();
    
    emit countChanged();  // <-- emit count changed here

}

void ParameterModel::setParameterValue(int row, const QVariant &value) 
{
    if (row < 0 || row >= mItems.size()) 
    {   
        return;
    }

    Parameter* p = mItems.at(row);
    QVariant old = p->getValue();
    if (old != value) 
    {
        p->setValue(value);
        QModelIndex idx = index(row);
        emit dataChanged(idx, idx, {ValueRole});
    }
}
