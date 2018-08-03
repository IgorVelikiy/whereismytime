#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <memory>
#include <QMainWindow>
#include <windows.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    struct Translation
    {
        WORD language;
        WORD codePage;
    };
    Ui::MainWindow *ui;
    const QStringList headers{"Application", "Time"};
    std::unique_ptr<QString> getAppName();
};

#endif // MAINWINDOW_H
