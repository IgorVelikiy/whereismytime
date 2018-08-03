#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QFile>
#include <QTime>
#include <QtSql/QSqlError>
#include <QDebug>

class Database
{
private:
    QSqlDatabase db;
public:
    explicit Database(QString pathToFile = "D:/test/database.db");
    void addApp();
    QTime getAppTime(QString app);
    ~Database();
};

#endif // DATABASE_H
