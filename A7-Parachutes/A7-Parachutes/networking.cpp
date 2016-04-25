#include "networking.h"

Networking::Networking(QString configFile, QObject *parent)
    : url(), debug(false), QObject(parent)
{
    // Get the settings from the ini file.
    QSettings* socketSettings = new QSettings(configFile, QSettings::IniFormat);
    socketSettings->beginGroup("socket");
    QString scheme = socketSettings->value("scheme", QString("ws")).toString();
    QString host = socketSettings->value("host", QString("localhost")).toString();
    int port = socketSettings->value("port", 8081).toInt();
    debug = socketSettings->value("debug", false).toBool();

    // Set the url to connect to
    url.setScheme(scheme);
    url.setHost(host);
    url.setPort(port);

    if (debug)
        qDebug() << "Attempting to connect to:" << url;

    connect(&webSocket, &QWebSocket::connected, this, &Networking::onConnected);
    connect(&webSocket, &QWebSocket::disconnected, this, &Networking::socketClosed);
    connect(&webSocket, static_cast<void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
            [=](QAbstractSocket::SocketError error) {
            if (debug)
                qDebug() << "Error:" << error;
        });

    webSocket.open(QUrl(url));
}

Networking::~Networking() {}

/*!
 * \brief Sends a request to the server for the list of words.
 * \param teacher
 * \param listName
 */
void Networking::requestWordList(QString teacher, QString listName)
{
    QJsonObject requestObject;
    requestObject["requestType"] = WordList;
    requestObject["teacher"] = teacher;
    requestObject["listName"] = listName;

    QJsonDocument requestDocument(requestObject);
    webSocket.sendTextMessage(requestDocument.toJson(QJsonDocument::Compact));
}

/////////////////////////////////
///////////// SLOTS /////////////
/////////////////////////////////

/*!
 * \brief Networking::onConnected
 */
void Networking::onConnected()
{
    if (debug)
        qDebug() << "WebSocket connected to server:" << url;

    // Start listening for a message from the server:
    connect(&webSocket, &QWebSocket::textMessageReceived, this, &Networking::onTextMessageReceived);
    connect(&webSocket, &QWebSocket::binaryMessageReceived, this, &Networking::onBinaryMessageReceived);

    requestWordList("teacher", "listname");
//    webSocket.sendTextMessage("Client: test");
}

/*!
 * \brief Networking::onTextMessageReceived
 * \param message
 */
void Networking::onTextMessageReceived(QString message)
{
    if (debug)
        qDebug() << "Text message received" << message;

    // Convert the received message to a json document:
    QJsonDocument receivedDocument = QJsonDocument::fromJson(message.toUtf8());
    if (receivedDocument.isObject())
    {
        // convert the document to a json object:
        QJsonObject receivedObject = receivedDocument.object();
        for (QJsonObject::iterator itr = receivedObject.begin(); itr != receivedObject.end(); ++itr)
        {
            if (itr.key() == "wordList")
            {
                if (debug)
                    qDebug() << "wordList is found";
                QJsonArray wordList = itr.value().toObject()["list"].toArray();
                printJsonArray(wordList);
            }
        }
    } else {
        Q_EMIT receiveError(message);
        if (debug)
            qDebug() << "Error! Unkown JSON Object:" << message;
        // TODO: Send error message to server
    }
}

/*!
 * \brief Networking::onBinaryMessageReceived
 * \param data
 */
void Networking::onBinaryMessageReceived(QByteArray data)
{
    if (debug)
        qDebug() << "Binary message received" << data;
}

/*!
 * \brief Prints out the first dimension of the json object for debugging.
 * \param json
 */
void Networking::printJsonObject(QJsonObject &json)
{
    qDebug() << "---------------------JSON Object------------------------";
    for(QJsonObject::iterator itr = json.begin(); itr != json.end(); ++itr)
    {
        qDebug() << "key:" << itr.key();
        qDebug() << "value:" << itr.value();
    }
    qDebug() << "--------------------------------------------------------";
}

void Networking::printJsonArray(QJsonArray &array)
{
    qDebug() << "---------------------JSON Array-------------------------";
    for(QJsonValue value : array)
    {
        qDebug() << value;
    }
    qDebug() << "--------------------------------------------------------";
}

/*!
 * \brief Used to test sending JSON documents between client and server.
 * \param message
 */
void Networking::testJson(QString message)
{
    qDebug() << "Message Received:" << message;

    QJsonDocument document = QJsonDocument::fromJson(message.toUtf8());

    qDebug() << "-------------------------------------------------------------------------------------";

    QJsonObject object = document.object();
    QJsonValue value = object.value(QString("appName"));

    qWarning() << value;
    qDebug() << "--------------------------------------------------------";

    QJsonObject item = value.toObject();

    qWarning() << tr("QJsonObject of descripiton: ") << item;
    qDebug() << "--------------------------------------------------------";

    // incase of string value get value and convert into string
    qWarning() << tr("QJsonObject[appName] of description: ") << item["description"];
    qDebug() << "--------------------------------------------------------";
    QJsonValue subObject = item["description"];
    qWarning() << subObject.toString();
    qDebug() << "--------------------------------------------------------";

    // incase of array get array and convert into string
    qWarning() << tr("QJsonObject[appName] of value: ") << item["imp"];
    qDebug() << "--------------------------------------------------------";
    QJsonArray subArray = item["imp"].toArray();
    qWarning() << subArray[1].toString();

    qDebug() << "-------------------------------------------------------------------------------------";
}