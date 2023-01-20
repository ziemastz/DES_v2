#ifndef DECAYSCHEMEMODEL_H
#define DECAYSCHEMEMODEL_H

#include "Models/nuclidemodel.h"
#include "Models/branchmodel.h"

class DecaySchemeModel
{
public:
    NuclideModel radionuclide;
    QList<BranchModel> branches;
};

#endif // DECAYSCHEMEMODEL_H
