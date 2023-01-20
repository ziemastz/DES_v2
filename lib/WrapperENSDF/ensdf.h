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
    ParentRecord getParent() const;


    QVector<LevelRecord> getLevel() const;

    QMap<int, BetaRecord> getBeta() const;

    QMap<int,AlphaRecord> getAlpha() const;

    QMap<int,ECRecord> getEC() const;

    QMap<int, QVector<GammaRecord> > getGamma() const;

protected:
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
