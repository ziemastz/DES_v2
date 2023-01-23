#ifndef BRANCHMODEL_H
#define BRANCHMODEL_H

#include <QObject>
#include "Models/gammamodel.h"
#include "Models/nuclidemodel.h"
#include "Models/levelmodel.h"

class BranchModel
{
public:
    NuclideModel parent;
    QString transition;
    QString intensity;
    LevelModel level;
    NuclideModel daughter;

    QList<GammaModel> gammes;

};

#endif // BRANCHMODEL_H
