#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
class Database
{
public:
    Database();
    ~Database();

    static void setDriver(const QString &newDriver);
    static void setDatabaseName(const QString &newDatabaseName);

    bool write(const QString& statement);
    QVector<QVariantList> read(const QString& statement);

    int getLastInsertId() const;

private:
    static QString _driver;
    static QString _databaseName;
    QSqlDatabase *_db;
    QSqlQuery *_query;
    QString _connectionName;
    int lastInsertId;
};

#endif // DATABASE_H
