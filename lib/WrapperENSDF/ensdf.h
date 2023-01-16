#ifndef ENSDF_H
#define ENSDF_H
#include <QVector>
#include <QMap>
#include "recordensdf.h"

#include "identificationrecord.h"
#include "parentrecord.h"
#include "normalizationrecord.h"
#include "productionnormalizationrecord.h"
#include "levelrecord.h"
#include "betarecord.h"
#include "ecrecord.h"
#include "alpharecord.h"
#include "gammarecord.h"

class ENSDF
{
public:
    ENSDF();
    void setIdentification(const RecordENSDF &line);
    void setParent(const RecordENSDF &line);
    void setNormalization(const RecordENSDF &line);
    void setProductionNormalization(const RecordENSDF &line);
    void setLevel(const RecordENSDF &line);
    void setBeta(const RecordENSDF &line);
    void setEC(const RecordENSDF &line);
    void setAlpha(const RecordENSDF &line);
    void setGamma(const RecordENSDF &line);

    void setEnd(const RecordENSDF &line);

private:
    IdentificationRecord id;
    ParentRecord parent;
    NormalizationRecord normalization;
    ProductionNormalizationRecord productionNormalization;
    QVector<LevelRecord> level;
    QMap<int,BetaRecord> beta;
    QMap<int,ECRecord> ec;
    QMap<int,AlphaRecord> alpha;
    QMap<int,QVector<GammaRecord> > gamma;
};

#endif // ENSDF_H
