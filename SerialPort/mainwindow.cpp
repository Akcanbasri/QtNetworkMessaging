#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    serial = new QSerialPort(this);

    connect(serial, &QSerialPort::readyRead, this, &MainWindow::on_readData);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_connectButton_clicked() {
    serial->setPortName(ui->portNameEdit->text());
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite)) {
        ui->statusLabel->setText("Connected");
    } else {
        ui->statusLabel->setText("Failed to connect");
    }
}

void MainWindow::on_sendButton_clicked() {
    QByteArray data = ui->sendDataEdit->text().toUtf8();
    serial->write(data);
}

void MainWindow::on_readData() {
    QByteArray data = serial->readAll();
    ui->receivedDataEdit->setText(data);
}
