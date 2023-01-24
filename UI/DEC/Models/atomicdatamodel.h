#ifndef ATOMICDATAMODEL_H
#define ATOMICDATAMODEL_H

#include <QString>
#include <QStringList>
#include <QMap>

class AtomicDataModel
{
public:
    QString radius;
    //fluorescence Yields
    QMap<QString,QString> fluorescenceYields; // <1, 2> 1:subshell, 2:intensity
    //Coster-Kronig Yields
    QString f12;
    QString f13;
    QString f23;

};

#endif // ATOMICDATAMODEL_H
