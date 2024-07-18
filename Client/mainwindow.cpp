#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , client(new Client(this))
{
    ui->setupUi(this);
    setWindowTitle("Client");
    client->connectToServer();
    connect(client, &Client::messageReceived, this, &MainWindow::displayMessage);
    connect(client, &Client::messageSent, this, &MainWindow::logSentMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayMessage(const QString &message)
{
    ui->logTextEdit->append("Received: " + message);
}

void MainWindow::logSentMessage(const QString &message)
{

    ui->logTextEdit->append("Sent: " + message);
}
