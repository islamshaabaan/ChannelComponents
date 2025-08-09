#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ChannelManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ChannelManager manager;
    bool ok = manager.loadFromFile(QStringLiteral("D:/Courses/Qt6CPP/Qt6CppGUIDevelopmentforBeginners/ChannelsGenerator/data/channels.json")); // ensure this file is next to exe or give full path
    if (!ok) 
    {
        qWarning() << "Failed to load channels.json";
    }

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("channelManager", &manager);
    QString qmlPath = QCoreApplication::applicationDirPath() + "/../qml/main.qml";
    engine.load(QUrl::fromLocalFile("D:/Courses/Qt6CPP/Qt6CppGUIDevelopmentforBeginners/ChannelsGenerator/qml/main.qml"));
    if (engine.rootObjects().isEmpty()) return -1;

    return app.exec();
}
