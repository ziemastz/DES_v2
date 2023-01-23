#ifndef BRANCHMODEL_H
#define BRANCHMODEL_H

#include <QObject>
#include "Models/gammamodel.h"
#include "Models/nuclidemodel.h"
#include "Models/levelmodel.h"
#include "Models/ecmodel.h"
class BranchModel
{
public:
    NuclideModel parent;
    QString transition;
    QString intensity;
    LevelModel level;
    NuclideModel daughter;

    QList<GammaModel> gammes;

    //alpha
    QString alpha_energy_kev;
    //beta-
    //ec (or EC + Beta+)
    ECModel ec;
};

#endif // BRANCHMODEL_H
