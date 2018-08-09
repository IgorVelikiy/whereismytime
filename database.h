#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QFile>
#include <memory>
#include "timer.h"

class Database
{
private:
    QSqlDatabase                      db;
public:
    std::unique_ptr<QSqlTableModel>   tableModel;

    explicit Database(const QString pathToFile = "database.db");

    void addApp(const QString appName);
    std::unique_ptr<Timer> getAppTime(const QString appName) const;
    void setAppTime(const QString appName, const QString appTime);
};

#endif // DATABASE_H
