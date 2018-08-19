#ifndef TRAY_H
#define TRAY_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>
#include <QAction>

class Tray : public QWidget
{
    Q_OBJECT
public:
    explicit Tray(QWidget *parent = nullptr);

signals:
    void doubleClick(QSystemTrayIcon::ActivationReason reason);
    void contextMenuExit();
public slots:
private:
    QSystemTrayIcon trayIcon;
};

#endif // TRAY_H
