#ifndef BRANCHMODEL_H
#define BRANCHMODEL_H

#include <QObject>
#include "Models/nuclidemodel.h"
#include "Models/gammamodel.h"

class BranchModel
{
public:
    NuclideModel parent;
    QString transition;
    QString intensity;
    QString excited_level_keV;
    NuclideModel daughter;

    QList<GammaModel> gammes;

};

#endif // BRANCHMODEL_H
