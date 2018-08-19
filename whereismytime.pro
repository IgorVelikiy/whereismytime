QT       += core gui widgets
QT += sql

TARGET = whereismytime
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    database.cpp \
    timer.cpp \
    tray.cpp

HEADERS += \
        mainwindow.h \
    database.h \
    timer.h \
    tray.h

FORMS += \
        mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
