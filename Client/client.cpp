#include "client.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

Client::Client(QObject *parent) : QObject(parent), tcpSocket(new QTcpSocket(this))
{
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Client::receiveMessage);
}

void Client::connectToServer()
{
    tcpSocket->connectToHost("127.0.0.1", 1234);
    if (tcpSocket->waitForConnected(3000)) {
        qDebug() << "Connected to server";
    } else {
        qDebug() << "Connection to server failed: " << tcpSocket->errorString();
    }
}

void Client::sendMessage(const QString &message)
{
    if (tcpSocket->isOpen()) {
        QJsonObject jsonObject;
        jsonObject["message"] = message;
        QJsonDocument jsonDoc(jsonObject);
        tcpSocket->write(jsonDoc.toJson());
        emit messageSent(message);
    }
}

void Client::receiveMessage()
{
    QByteArray data = tcpSocket->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObject = jsonDoc.object();
    QString message = jsonObject["message"].toString();
    qDebug() << "Received:" << message;
    emit messageReceived(message);

    sendMessage("Hello, Server! How Are you");
}
