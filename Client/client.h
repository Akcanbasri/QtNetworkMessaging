#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    void connectToServer();
    void sendMessage(const QString &message);

signals:
    void messageReceived(const QString &message);
    void messageSent(const QString &message);

private slots:
    void receiveMessage();

private:
    QTcpSocket *tcpSocket;
};

#endif // CLIENT_H
