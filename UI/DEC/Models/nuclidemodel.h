#ifndef NUCLIDEMODEL_H
#define NUCLIDEMODEL_H

#include <QObject>

class NuclideModel
{
public:
    NuclideModel();

    QString getSymbol() const;
    void setSymbol(const QString &newSymbol);

    QString getHalfLifeValue() const;
    void setHalfLifeValue(const QString &newHalfLifeValue);

    QString getHalfLifeUncertainty() const;
    void setHalfLifeUncertainty(const QString &newHalfLifeUncertainty);

    QString getHalfLifeUnit() const;
    void setHalfLifeUnit(const QString &newHalfLifeUnit);

    QString getRadius() const;
    void setRadius(const QString &newRadius);

    QString getSpinParity() const;
    void setSpinParity(const QString &newSpinParity);

private:
    QString symbol;

    QString halfLifeValue;
    QString halfLifeUncertainty;
    QString halfLifeUnit;

    QString radius;

    QString spinParity;

};

#endif // NUCLIDEMODEL_H
