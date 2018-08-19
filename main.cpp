#include "mainwindow.h"
#include <QApplication>
#include <database.h>
#pragma comment(lib,"user32")
#pragma comment(lib,"version")
#include <future>
#include "tray.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Tray tray;
    QObject::connect(&a, SIGNAL(aboutToQuit()), &w, SLOT(stopTimeUpdater()));
    QObject::connect(&tray, SIGNAL(doubleClick(QSystemTrayIcon::ActivationReason)), &w, SLOT(showOnDoubleClicked(QSystemTrayIcon::ActivationReason)));
    QObject::connect(&tray, SIGNAL(contextMenuExit()), &a, SLOT(quit()));
    auto tmp = std::async(std::launch::async, [&w]{
        w.timeUpdater();
    });
    w.show();
    return a.exec();
}
