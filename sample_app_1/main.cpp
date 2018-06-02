#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "datastore.h"
#include "memsdata.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQmlContext* context = engine.rootContext();
    datastore ds;
    context->setContextProperty("dataStore", &ds);

    MemsData data;
    context->setContextProperty("memsData", &data);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
