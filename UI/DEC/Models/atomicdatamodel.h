#ifndef ATOMICDATAMODEL_H
#define ATOMICDATAMODEL_H

#include <QString>
#include <QMap>
#include "Models/atomicsubshellmodel.h"

class AtomicDataModel
{
public:
    //fluorescence Yields
    QMap<QString,QString> fluorescenceYields; // <1, 2> 1:subshell, 2:intensity
    //Coster-Kronig Yields
    QString f12;
    QString f13;
    QString f23;
    //atomic Subshells
    QMap<QString, AtomicSubshellModel> atomicSubshells;
};

#endif // ATOMICDATAMODEL_H
