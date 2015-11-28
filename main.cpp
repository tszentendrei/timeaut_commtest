#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include "RobotState.h"
#include "communication.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    RobotState robot;
    Communication c;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("robot", &robot);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    c.connect();
    QTimer::singleShot(2000, &c, SLOT(doComm()));
    QObject::connect(&c, SIGNAL(msgReady(QDataStream&)), &robot, SLOT(processMsg(QDataStream&)));

    return app.exec();
}

