#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <database.h>
#include <psapi.h>
#include <Strsafe.h>
#include <thread>
#include <chrono>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void timeUpdater();
public slots:
    void stopTimeUpdater();
private:
    struct Translation
    {
        WORD language;
        WORD codePage;
    };
    bool                isWork = true;
    Ui::MainWindow      *ui;
    Database            db;
    const QStringList   headers{"Application", "Time"};

    QString getAppName() const;  
};

#endif // MAINWINDOW_H
