#include "mainwindow.h"
#include <QApplication>
#include <database.h>
#pragma comment(lib,"user32")
#pragma comment(lib,"version")

int main(int argc, char *argv[])
{
    Database db("D:/test/database.db");
    auto t = db.getAppTime("firstApp");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
