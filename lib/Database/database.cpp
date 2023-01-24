#include "database.h"

QString Database::_driver = "";
QString Database::_databaseName = "";

Database::Database()
{
}

void Database::setDriver(const QString &newDriver)
{
    if(QSqlDatabase::isDriverAvailable(newDriver)) {
        _driver = newDriver;
        qInfo() << "Set new driver of database: " << _driver;
    }else {
        qWarning() << "No database driver: " << newDriver << " Current driver: " << _driver;
    }
}

void Database::setDatabaseName(const QString &newDatabaseName)
{
    _databaseName = newDatabaseName;
    qInfo() << "Set new name of database: " << _databaseName;
}

bool Database::write(const QString &statement)
{
    QString connectionName;
    bool ret = false;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(_driver);
        db.setDatabaseName(_databaseName);
        if(db.open()) {
            connectionName = db.connectionName();
            QSqlQuery query;
            if(query.exec(statement))
            {
                lastInsertId = query.lastInsertId().toInt();
                ret = true;
            }else{
                qWarning() << "Wrong writing query: " << query.lastError().text();
                ret = false;
            }
        }else {
            qWarning() << "Error opening of database: " << db.lastError().text();
            ret = false;
        }
    }
    QSqlDatabase::removeDatabase(connectionName);
    return ret;
}

QVector<QVariantList> Database::read(const QString &statement)
{
    QString connectionName;
    QVector<QVariantList> ret;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(_driver);
        db.setDatabaseName(_databaseName);
        if(db.open()) {
            connectionName = db.connectionName();
            QSqlQuery query;
            if(query.exec(statement))
            {
                while(query.next())
                {
                    QVariantList record;
                    for(int i=0;i<query.record().count();i++)
                    {
                        record << query.value(i);
                    }
                    ret << record;
                }
            }else{
                qWarning() << "Wrong reading query: " << query.lastError().text();
            }
        }else {
            qWarning() << "Error opening of database: " << db.lastError().text();
        }
    }
    QSqlDatabase::removeDatabase(connectionName);
    return ret;
}

int Database::getLastInsertId() const
{
    return lastInsertId;
}
