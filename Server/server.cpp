#include "server.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>

Server::Server(QObject *parent) : QObject(parent), tcpServer(new QTcpServer(this)), clientSocket(nullptr)
{
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::newConnection);
}

void Server::startServer()
{
    if (!tcpServer->listen(QHostAddress::Any, 1234)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started!";
    }
}

void Server::sendMessage(const QString &message)
{
    if (clientSocket && clientSocket->isOpen()) {
        QJsonObject jsonObject;
        jsonObject["message"] = message;
        QJsonDocument jsonDoc(jsonObject);
        clientSocket->write(jsonDoc.toJson());
    }
}

void Server::newConnection()
{
    clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::receiveMessage);
    qDebug() << "New connection";
}

void Server::receiveMessage()
{
    QByteArray data = clientSocket->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObject = jsonDoc.object();
    QString message = jsonObject["message"].toString();
    qDebug() << "Received:" << message;
    emit messageReceived(message);
}
