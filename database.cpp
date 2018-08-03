#include "database.h"

Database::Database(QString pathToFile)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(pathToFile);
    if (!QFile(pathToFile).exists() & db.open())
    {
        db.exec( "CREATE TABLE main "
                                "("
                                    "Application    TEXT            NOT NULL    PRIMARY KEY,"
                                    "Time           TIME            NOT NULL                "
                                ")"
                            );
        db.exec("INSERT INTO main VALUES ('firstApp', '25:35:65')");
    }
}

void Database::addApp()
{

}

QTime Database::getAppTime(QString app)
{
    auto q = db.exec("SELECT * FROM main WHERE Application = '"+app+"'");
    if (q.next())
    {
        return QTime::fromString(q.value(1).toString(), "hh:mm:ss");
    }
}

Database::~Database()
{
    db.commit();
}
