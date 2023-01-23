#ifndef NUCLIDEMODEL_H
#define NUCLIDEMODEL_H

#include <QObject>

class NuclideModel
{
public:
    QString symbol;

    QString halfLifeValue;
    QString halfLifeUncertainty;
    QString halfLifeUnit;

    QString radius;

    QString spinParity;

};

#endif // NUCLIDEMODEL_H
