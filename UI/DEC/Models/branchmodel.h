#ifndef BRANCHMODEL_H
#define BRANCHMODEL_H

#include <QObject>
#include <QVector>
#include "Models/gammamodel.h"
#include "Models/nuclidemodel.h"
#include "Models/levelmodel.h"
#include "Models/ecmodel.h"
#include "Models/betatransitionmodel.h"

class BranchModel
{
public:
    uint id;
    NuclideModel parent;
    QString transition;
    double intensity;
    LevelModel level;
    NuclideModel daughter;

    QVector<GammaModel> gammes;

    //alpha
    QString alpha_energy_kev;
    //beta-
    BetaTransitionModel beta;
    //ec (or EC + Beta+)
    ECModel ec;
};

#endif // BRANCHMODEL_H
