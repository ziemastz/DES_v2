#include "atomicsubshellmodel.h"



AtomicSubshellModel &AtomicSubshellModel::operator =(const AtomicSubshellModel &other)
{
    this->binding_energy_keV = other.binding_energy_keV;
    this->elektrons_max = other.elektrons_max;
    this->auger = other.auger;
    this->xRay = other.xRay;
    return *this;
}

QStringList AtomicSubshellModel::getSubshells() const
{
    return subshells;
}

QStringList AtomicSubshellModel::getSubshells(const QString &fromSubshell) const
{
    QStringList ret;
    int index = subshells.indexOf(fromSubshell);
    for(int i=index+1; i<subshells.size(); i++) {
        ret << subshells.at(i);
    }
    return ret;
}
