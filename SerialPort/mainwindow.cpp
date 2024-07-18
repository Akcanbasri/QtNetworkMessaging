#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) // Constructor fonksiyonunun tanımı
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    serial = new QSerialPort(this); // serial pointerı ile bir seri port nesnesi oluşturuyoruz.

    connect(serial, &QSerialPort::readyRead, this, &MainWindow::on_readData); // connect işlemi ile readyRead sinyali alındığında on_readData fonksiyonunu tetikler
}

MainWindow::~MainWindow() {
    delete ui;
} // Deconstructor fonksiyonu tanımı


// bağlantı için araştırdığım kaynaklar:
// https://cboard.cprogramming.com/cplusplus-programming/169624-read-write-serial-port.html
// https://www.youtube.com/watch?v=UD78xyKbrfk
// https://stackoverflow.com/questions/43203447/how-to-write-data-to-a-given-serial-port-with-qt
// https://www.youtube.com/watch?v=LahsPOaLOVo
// https://doc.qt.io/qt-6/qtserialport-index.html


void MainWindow::on_connectButton_clicked() { // Butona tıklandığında çağrılacak slot fonksiyonu.
    serial->setPortName(ui->portNameEdit->text());
    serial->setBaudRate(QSerialPort::Baud9600);  // Seri haberleşmede veri hızının ayarlanması
    serial->setDataBits(QSerialPort::Data8);  // veri bitlerini 8 bit olarak ayarlar
    serial->setParity(QSerialPort::NoParity); // Parite yok
    serial->setStopBits(QSerialPort::OneStop);  // Dur biti 1 olarak verilir bu sayede alıcı iletimin bittiğini ve bir sonraki mesajın geleceğinden haberdar olur.
    serial->setFlowControl(QSerialPort::NoFlowControl); // akış kontrolu(donanım ve yazılım tabanlı) olmadığını ayarlarız.

    if (serial->open(QIODevice::ReadWrite)) { // QIODevice::ReadWrite ile seri portu okuma yazma ile açmayı dener. bu sayede akış kontrolü ile bağlanıp bağlanmadığını kontrol ederiz.
        ui->statusLabel->setText("Connected");
    } else {
        ui->statusLabel->setText("Failed to connect");
    }
}

void MainWindow::on_sendButton_clicked() { // çağrılan slot fonksionu
    QByteArray data = ui->sendDataEdit->text().toUtf8(); // UTF-8 formatında verileri dönüştür ve veriyi port üzerinden alıcıya gönderir
    serial->write(data);
}

void MainWindow::on_readData() { // eğer veri alıcıya gelirse çalışan slot fonksiyonu
    QByteArray data = serial->readAll(); // Seri porttan gelen tüm verileri okur.
    ui->receivedDataEdit->setText(data);
}
