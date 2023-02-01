#ifndef ATOMICDATAMODEL_H
#define ATOMICDATAMODEL_H

#include "Models/atomicsubshellmodel.h"
#include <QString>
#include <QStringList>
#include <QMap>

class AtomicDataModel
{
public:
    double radius;
    //fluorescence Yields
    QMap<QString, double> fluorescenceYields; // <1, 2> 1:subshell, 2:intensity
    //Coster-Kronig Yields
    double f12;
    double f13;
    double f23;

    QMap<QString, AtomicSubshellModel> subshells;

};

#endif // ATOMICDATAMODEL_H
