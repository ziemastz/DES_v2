#include "database.h"

Database *Database::_instance = nullptr;
QString Database::_driver = "";
QString Database::_databaseName = "";

Database::Database()
{
    _query = nullptr;
    _db = nullptr;
}

Database::~Database()
{
    if(_query != nullptr) {
        _query->finish();
        delete _query;
    }
    if(_db != nullptr) {
        _db->close();
        delete _db;
        QSqlDatabase::removeDatabase(_connectionName);
    }
}

Database *Database::database()
{
    if(_instance == nullptr) {
        _instance = new Database();
    }
    return _instance;
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
    if(_db == nullptr) {
        _db = new QSqlDatabase;
        *_db = QSqlDatabase::addDatabase(_driver,QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz"));
        _db->setDatabaseName(_databaseName);
    }

    if(!_db->isOpen()) {
        if(!_db->open()) {
            qWarning() << "Error opening of database: " << _db->lastError().text();
            return false;
        }
        _connectionName = _db->connectionName();
        _query = new QSqlQuery(*_db);
    }

    if(_query->exec(statement)) {
        lastInsertId = _query->lastInsertId().toUInt();
        return true;
    }else {
        qWarning() << "Wrong writing query: " << _query->lastError().text();
        return false;
    }
}

QVector<QVariantList> Database::read(const QString &statement)
{
    QVector<QVariantList> ret;

    if(_db == nullptr) {
        _db = new QSqlDatabase;
        *_db = QSqlDatabase::addDatabase(_driver,QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz"));
        _db->setDatabaseName(_databaseName);
    }

    if(!_db->isOpen()) {
        if(!_db->open()) {
            qWarning() << "Error opening of database: " << _db->lastError().text();
            return ret;
        }
        _connectionName = _db->connectionName();
        _query = new QSqlQuery(*_db);
    }

    if(_query->exec(statement)) {
        while(_query->next())
        {
            QVariantList record;
            for(int i=0;i<_query->record().count();i++)
            {
                record << _query->value(i);
            }
            ret << record;
        }
        return ret;
    }else {
        qWarning() << "Wrong writing query: " << _query->lastError().text();
        return ret;
    }
}

uint Database::getLastInsertId() const
{
    return lastInsertId;
}
