#include "mainwindow.h"
#include <QApplication>
#include <database.h>
#pragma comment(lib,"user32")
#pragma comment(lib,"version")
#include <future>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QObject::connect(&a, SIGNAL(lastWindowClosed()), &w, SLOT(stopTimeUpdater()));
    auto tmp = std::async(std::launch::async, [&w]{
        w.timeUpdater();
    });
    w.show();

    return a.exec();
}

/*
   TODO:
    * minimizing to tray
    * update table only when reminimize
    * set path to database
    * full-width columns
    * localization
    * optimize disk accesses?
*/
