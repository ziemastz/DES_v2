#ifndef BRANCHMODEL_H
#define BRANCHMODEL_H

#include <QObject>
#include "Models/gammamodel.h"

class BranchModel
{
public:
    QString parent;
    QString transition;
    QString intensity;
    QString excited_level_keV;
    QString daughter;

    QList<GammaModel> gammes;

};

#endif // BRANCHMODEL_H
