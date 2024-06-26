#include "atomicsubshellmodel.h"



AtomicSubshellModel::AtomicSubshellModel()
{
    binding_energy_eV = 0.0;
    availablelElectrons = 0.0;
    elektrons_max = 0.0;
}

AtomicSubshellModel &AtomicSubshellModel::operator =(const AtomicSubshellModel &other)
{
    this->binding_energy_eV = other.binding_energy_eV;
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
