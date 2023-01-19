#include "branchmodel.h"

BranchModel::BranchModel()
{

}

NuclideModel BranchModel::getParent() const
{
    return parent;
}

void BranchModel::setParent(const NuclideModel &newParent)
{
    parent = newParent;
}

QString BranchModel::getTransition() const
{
    return transition;
}

void BranchModel::setTransition(const QString &newTransition)
{
    transition = newTransition;
}

QString BranchModel::getIntensity() const
{
    return intensity;
}

void BranchModel::setIntensity(const QString &newIntensity)
{
    intensity = newIntensity;
}

QString BranchModel::getExcited_level_keV() const
{
    return excited_level_keV;
}

void BranchModel::setExcited_level_keV(const QString &newExcited_level_keV)
{
    excited_level_keV = newExcited_level_keV;
}

NuclideModel BranchModel::getDaughter() const
{
    return daughter;
}

void BranchModel::setDaughter(const NuclideModel &newDaughter)
{
    daughter = newDaughter;
}
