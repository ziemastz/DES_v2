#ifndef DECAYSCHEMEMODEL_H
#define DECAYSCHEMEMODEL_H

#include "Models/branchmodel.h"

class DecaySchemeModel
{
public:
    QString radionuclide;
    QList<BranchModel> branches;
};

#endif // DECAYSCHEMEMODEL_H
