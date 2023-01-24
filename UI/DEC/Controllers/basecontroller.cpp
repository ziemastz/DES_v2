#include "basecontroller.h"
#include <QFile>
BaseController::BaseController()
{
    qDebug() << "BaseController contructor";
    //config database for SQLITE
    QString driver = "QSQLITE";
    QString databaseName = "des_1.db";
    QString path = databaseName;
    QString resourcePath = "://DB/des_1.db";

    if(!QFile::exists(path)) {
        qDebug() << "Missing database file: " << path;
        if(QFile::copy(resourcePath,path)) {
            qDebug() << "The database file was copy from resource";
            if(QFile(path).setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner))
                qDebug() << "The database file was set permision";
            else
                qWarning() << "The database file wasn't set permision";
        }else
            qWarning() << "Error coping database file from " <<resourcePath << " to " <<path;
    }
    Database::setDriver(driver);
    Database::setDatabaseName(databaseName);
}
