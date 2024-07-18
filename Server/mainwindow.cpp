#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , server(new Server(this))
{
    ui->setupUi(this);
    setWindowTitle("Server");
    server->startServer();
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendMessage);
    connect(server, &Server::messageReceived, this, &MainWindow::displayMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMessage()
{
    QString fileName = "D:/mepsan/Server/message.json";
    QFile file(fileName);
    if (!file.exists()) {
        qDebug() << "File does not exist:" << fileName;
        QMessageBox::warning(this, "Error", "JSON file does not exist!");
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open JSON file:" << fileName;
        QMessageBox::warning(this, "Error", "Could not open JSON file!");
        return;
    }

    QByteArray data = file.readAll();
    qDebug() << "Read data from file:" << data;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    if (jsonDoc.isNull()) {
        qDebug() << "Invalid JSON format";
        QMessageBox::warning(this, "Error", "Invalid JSON format!");
        return;
    }

    QJsonObject jsonObject = jsonDoc.object();
    QString message = jsonObject["message"].toString();
    qDebug() << "Message from JSON:" << message;

    server->sendMessage(message);
    ui->logTextEdit->append("Sent: " + message);
}

void MainWindow::displayMessage(const QString &message)
{
    ui->logTextEdit->append("Received: " + message);
}
