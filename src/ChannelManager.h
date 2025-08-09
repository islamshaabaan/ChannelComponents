#ifndef CHANNELMANAGER_H
#define CHANNELMANAGER_H

#include <QObject>
#include <QVector>
#include <QElapsedTimer>
#include "ParameterModel.h"

struct Channel 
{
    QString name;
    QList<Parameter*> parameters;
};

class ChannelManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QAbstractListModel* parameterModel READ parameterModel NOTIFY parameterModelChanged)

public:
    explicit ChannelManager(QObject* parent = nullptr);
    ~ChannelManager();

    QAbstractListModel* parameterModel() const;

    Q_INVOKABLE bool loadFromFile(const QString& path); // parse JSON and build channels
    Q_INVOKABLE void selectChannel(int index);         // choose channel -> populate model

    // QML calls this on user interaction: pass Date.now() from JS (ms epoch)
    Q_INVOKABLE void logInteraction(const QString& paramName,
                                    const QVariant& oldValue,
                                    const QVariant& newValue,
                                    qint64 jsTimestamp);

    Q_INVOKABLE int channelCount() const;
    Q_INVOKABLE QString channelName(int index) const;

signals:
    void parameterModelChanged();
    void channelsChanged();

private:
    QVector<Channel> mChannels;
    ParameterModel* mParameterModel;
};

#endif // CHANNELMANAGER_H
