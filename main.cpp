#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDateTime>

#include "logcontroller.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/LogCombinator/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    const QString logDirPath = "../LogCombinator";
    engine.rootContext()->setContextProperty("logDir", logDirPath);

    LogController logController;
    engine.rootContext()->setContextProperty("logController", &logController);

    engine.load(url);

    return app.exec();
}
