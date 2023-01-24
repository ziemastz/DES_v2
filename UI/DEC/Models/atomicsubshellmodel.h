#ifndef ATOMICSUBSHELLMODEL_H
#define ATOMICSUBSHELLMODEL_H

#include <QString>
#include <QMap>

class AtomicSubshellModel
{
public:
    QString binding_energy_keV;
    QString elektrons_max;
    QMap<QString,QString> auger;
    QMap<QString,QString> xRay;
};

#endif // ATOMICSUBSHELLMODEL_H
