#include "ChannelManager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QDateTime>

ChannelManager::ChannelManager(QObject* parent)
    : QObject(parent), mParameterModel(new ParameterModel(this))
{
}

ChannelManager::~ChannelManager() 
{
    // Owned children (Parameter objects) will be freed by Qt parent-child if parented to manager.
    for (auto &ch : mChannels) 
    {
        for (Parameter* p : ch.parameters) 
        {
            // delete if needed; but if parented to this, deletion will be automatic.
            p->deleteLater();
        }
    }
}

QAbstractListModel* ChannelManager::parameterModel() const 
{
    return mParameterModel;
}

bool ChannelManager::loadFromFile(const QString &path) 
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) 
    {
        qWarning() << "Could not open file:" << path;
        
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    f.close();

    if (!doc.isArray()) 
    {
        qWarning() << "Expected top-level array in the JSON file.";
        
        return false;
    }

    QJsonArray chArray = doc.array();
    for (const QJsonValue &cv : chArray) 
    {
        if (!cv.isObject()) 
        {
            continue;
        }

        QJsonObject chObj = cv.toObject();
        Channel ch;
        ch.name = chObj.value("channel_name").toString();

        QJsonArray params = chObj.value("parameters").toArray();
        for (const QJsonValue &pv : params) 
        {
            if (!pv.isObject()) 
            {
                continue;
            }

            QJsonObject po = pv.toObject();

            Parameter* p = new Parameter(this); // parented to ChannelManager
            p->setName(po.value("name").toString());
            p->setKind(po.value("kind").toString());
            p->setIsFixed(po.value("isfixed").toBool());

            QString kind = po.value("kind").toString();
            if (kind == "bool") 
            {
                p->setValue(po.value("Ivalue").toBool());
            } 
            else if (kind == "numeric") 
            {
                p->setValue(po.value("Ivalue").toDouble());
                p->setMin(po.value("min").toDouble());
                p->setMax(po.value("max").toDouble());
                p->setIsDecimal(po.value("isdecimal").toBool());
            } 
            else if (kind == "category") 
            {
                p->setValue(po.value("Ivalue").toInt());
                QJsonArray opts = po.value("options").toArray();
                QStringList sl;
                for (const QJsonValue &o : opts) sl << o.toString();
                p->setOptions(sl);
            }
            ch.parameters.append(p);
        }
        mChannels.append(ch);
        emit channelsChanged();
    }

    return true;
}

int ChannelManager::channelCount() const 
{
    return mChannels.size();
}

QString ChannelManager::channelName(int index) const 
{
    if (index < 0 || index >= mChannels.size()) return QString();
    return mChannels.at(index).name;
}
void ChannelManager::selectChannel(int index) {
    if (index < 0 || index >= mChannels.size()) {
        qWarning() << "selectChannel: out of range" << index;
        return;
    }

    QElapsedTimer t; t.start();
    // supply the ParameterModel the pointers for the selected channel
    mParameterModel->setParameters(mChannels[index].parameters);
    qint64 elapsed = t.elapsed();
    if (elapsed > 100) {
        qWarning() << "Channel loading took" << elapsed << "ms > 100ms";
    } else {
        qDebug() << "Channel loaded in" << elapsed << "ms";
    }
    emit parameterModelChanged();
}

void ChannelManager::logInteraction(const QString &paramName,
                                    const QVariant &oldValue,
                                    const QVariant &newValue,
                                    qint64 jsTimestamp)
{
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    qint64 latency = now - jsTimestamp;
    qDebug().noquote() << QString("Interaction: %1  %2 -> %3  jsTs=%4  cTs=%5  latency=%6 ms")
                         .arg(paramName)
                         .arg(oldValue.toString())
                         .arg(newValue.toString())
                         .arg(jsTimestamp)
                         .arg(now)
                         .arg(latency);

    if (latency > 10) {
        qWarning() << "Interaction callback latency > 10ms:" << latency << "ms";
    }

    // Optionally append to a file or emit a signal for further processing.
}
