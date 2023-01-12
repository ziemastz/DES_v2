#ifndef ENSDFDATA_H
#define ENSDFDATA_H

#include <QObject>
#include "id.h"
#include "parentdata.h"
#include "normalization.h"
#include "leveldata.h"
#include "betadata.h"
#include "alpha.h"
#include "ec.h"
#include "gamma.h"

class ENSDFData
{
public:
    ENSDFData();
    ID id;
    ParentData parent;
    NormalizationData normalization;
    QVector<LevelData> level;
    QVector<BetaData> beta;
    QVector<Alpha> alpha;
    QVector<EC> ec;
    QVector<Gamma> gamma;
};

#endif // ENSDFDATA_H
