#include <QApplication>
#include <QDesktopWidget>
#include "mainwindow.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Fire Fire Fire!!!");

    QDesktopWidget *desktop = new QDesktopWidget();
    w.move((desktop->width() - w.size().width())/2, (desktop->height() - w.size().height())/2);

    w.show();
    
    return a.exec();
}
