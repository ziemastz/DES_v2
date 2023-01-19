#include "nuclidemodel.h"

NuclideModel::NuclideModel()
{

}

QString NuclideModel::getSymbol() const
{
    return symbol;
}

void NuclideModel::setSymbol(const QString &newSymbol)
{
    symbol = newSymbol;
}

QString NuclideModel::getHalfLifeValue() const
{
    return halfLifeValue;
}

void NuclideModel::setHalfLifeValue(const QString &newHalfLifeValue)
{
    halfLifeValue = newHalfLifeValue;
}

QString NuclideModel::getHalfLifeUncertainty() const
{
    return halfLifeUncertainty;
}

void NuclideModel::setHalfLifeUncertainty(const QString &newHalfLifeUncertainty)
{
    halfLifeUncertainty = newHalfLifeUncertainty;
}

QString NuclideModel::getHalfLifeUnit() const
{
    return halfLifeUnit;
}

void NuclideModel::setHalfLifeUnit(const QString &newHalfLifeUnit)
{
    halfLifeUnit = newHalfLifeUnit;
}

QString NuclideModel::getRadius() const
{
    return radius;
}

void NuclideModel::setRadius(const QString &newRadius)
{
    radius = newRadius;
}

QString NuclideModel::getSpinParity() const
{
    return spinParity;
}

void NuclideModel::setSpinParity(const QString &newSpinParity)
{
    spinParity = newSpinParity;
}
