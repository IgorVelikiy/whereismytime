#include "tray.h"

Tray::Tray(QWidget *parent)
    : QWidget(parent),
      trayIcon(QIcon(":/images/icon.xpm"))
{
    auto menu = new QMenu(this);
    menu->addAction(tr("Exit"));
    connect(*menu->actions().begin(), SIGNAL(triggered()), this, SIGNAL(contextMenuExit()));
    trayIcon.setContextMenu(menu);
    connect(&trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SIGNAL(doubleClick(QSystemTrayIcon::ActivationReason)));
    trayIcon.show();
}
