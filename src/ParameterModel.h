#ifndef PARAMETERMODEL_H
#define PARAMETERMODEL_H

#include <QAbstractListModel>
#include <QMetaObject>

#include "Parameter.h"

class ParameterModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        KindRole,
        ValueRole,
        MinRole,
        MaxRole,
        IsDecimalRole,
        OptionsRole,
        IsFixedRole
    };

    explicit ParameterModel(QObject* parent = nullptr);

    // model overrides
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // helpers
    void setParameters(const QList<Parameter*>& params); // reset model data
    Q_INVOKABLE void setParameterValue(int row, const QVariant& value); // callable from QML

private:
    QList<Parameter*> mItems;
    QVector<QMetaObject::Connection> mConnections;

};

#endif // PARAMETERMODEL_H
