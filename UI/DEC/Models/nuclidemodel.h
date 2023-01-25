#ifndef NUCLIDEMODEL_H
#define NUCLIDEMODEL_H

#include <QObject>

class NuclideModel
{
public:
    int id;
    int a;
    int z;
    QString symbol;

    double halfLifeValue;
    double halfLifeUncery;
    QString halfLifeUnit;

    QString spinParity;

    double radius;

};

#endif // NUCLIDEMODEL_H
