#include <QDebug>
#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QDir>
#include <QString>

// From 3rd party libraries
#include "staticfilecontroller.h"
#include "httplistener.h"       // HttpListener

// Application internals
#include "networking.h"
#include "mysqlwrapper.h"
#include "webserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Parse the command line for any options:
    QCommandLineParser parser;
    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for echoserver [default: 1234]."),
            QCoreApplication::translate("main", "port"), QLatin1Literal("1234"));
    parser.addOption(portOption);
    parser.process(app);
    // parser.value(portOption)
    // bool debug = parser.isSet(dbgOption);
    // int port = parser.value(portOption).toInt();

    // Get Settings from the config file:
    QString configFile = ":/A7-Server.ini";


    // QtWebApp:
    WebServer* httpServer = new WebServer(configFile, &app);

    // Start Web Socket Listener:
    Networking* server = new Networking(configFile, &app);
    QObject::connect(server, &Networking::closed, &app, &QCoreApplication::quit);
    server->getJsonDocument();

    return app.exec();
}
