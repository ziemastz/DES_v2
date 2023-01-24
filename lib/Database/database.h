#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QDebug>

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

    static void setDriver(const QString &newDriver);
    static void setDatabaseName(const QString &newDatabaseName);

    bool write(const QString& statement);
    QVector<QVariantList> read(const QString& statement);

    int getLastInsertId() const;

private:
    static QString _driver;
    static QString _databaseName;
    int lastInsertId;
};

#endif // DATABASE_H
