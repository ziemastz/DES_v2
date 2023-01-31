#ifndef NUCLIDEMODEL_H
#define NUCLIDEMODEL_H

#include <QObject>

class NuclideModel
{
public:
    int a;
    int z;
    QString symbol;

    double halfLifeValue;
    double halfLifeUncery;
    QString halfLifeUnit;

    QString spinParity;
};

#endif // NUCLIDEMODEL_H
