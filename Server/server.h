#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    void startServer();
    void sendMessage(const QString &message);

private slots:
    void newConnection();
    void receiveMessage();

signals:
    void messageReceived(const QString &message);

private:
    QTcpServer *tcpServer;
    QTcpSocket *clientSocket;
};

#endif // SERVER_H
