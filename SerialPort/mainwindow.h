#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort> // QT içindeki seri port kütüphanesini çağırıyoruz.
#include <QSerialPortInfo> // Seri Port bilgilerini elde etmek için QSerialPortInfo kütüphanesini çağırıyoruz.

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); // Constructor Fonkisyonu
    ~MainWindow(); // Deconstructer Fonksiyonu

private slots: // pivot slot kullanmamız encapsualtion prensibine uymamız için. dışardan erişim olmadan sadece ihtiyacı kadar veri dışarıya açmak için private slots kullandık.
    void on_connectButton_clicked(); // Connect Button tıklandığında çağrılan slot
    void on_sendButton_clicked(); // Send Button tıklandığında çağrılan slot
    void on_readData(); // seri porttan veri alındıktan sonra çağrılan slot

private:
    Ui::MainWindow *ui;
    QSerialPort *serial; // donanım seviyesinde iletişim kurmak için QSerialPort nesnesine ihtiyaç duyarız.
};

#endif // MAINWINDOW_H
