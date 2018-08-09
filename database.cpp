#include "database.h"
#include <QDebug>
#include <QSqlError>

Database::Database(const QString pathToFile)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(pathToFile);
    if (!QFile(pathToFile).exists() & db.open())
    {
        auto q = db.exec( "CREATE TABLE main "
                                "("
                                    "Application    TEXT            NOT NULL    PRIMARY KEY,"
                                    "Time           TIME            NOT NULL                "
                                ")"
                            );
    }
    tableModel = std::make_unique<QSqlTableModel>(nullptr, db);
    tableModel->setTable("main");
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->select();
    tableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Application"));
    tableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Time"));
}

void Database::addApp(const QString appName)
{
    db.exec("INSERT INTO main VALUES ('" + appName + "', '00:00:00.000')");
}

std::unique_ptr<Timer> Database::getAppTime(const QString app) const
{
    auto q = db.exec("SELECT * FROM main WHERE Application = '"+app+"'");
    if (!q.next())
        return nullptr;
    return std::make_unique<Timer>(q.value(1).toString().toLocal8Bit().constData());
}

void Database::setAppTime(const QString appName, const QString appTime)
{
    db.exec("UPDATE main SET Time='" + appTime + "' WHERE Application='" + appName + "'");
}
