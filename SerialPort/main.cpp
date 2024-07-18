#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv); // qt  uygulamasını başlatır
    MainWindow w; // sınıftan bir nesne oluşturur.
    w.show(); // Ana pencereyi gösterir
    return a.exec(); // uygulama döngüsünü başlatır.
}
