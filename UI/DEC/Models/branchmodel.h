#ifndef BRANCHMODEL_H
#define BRANCHMODEL_H

#include <QObject>
#include "Models/nuclidemodel.h"

class BranchModel
{
public:
    BranchModel();
    NuclideModel getParent() const;
    void setParent(const NuclideModel &newParent);

    QString getTransition() const;
    void setTransition(const QString &newTransition);

    QString getIntensity() const;
    void setIntensity(const QString &newIntensity);

    QString getExcited_level_keV() const;
    void setExcited_level_keV(const QString &newExcited_level_keV);

    NuclideModel getDaughter() const;
    void setDaughter(const NuclideModel &newDaughter);

private:
    NuclideModel parent;
    QString transition;
    QString intensity;
    QString excited_level_keV;
    NuclideModel daughter;

};

#endif // BRANCHMODEL_H
