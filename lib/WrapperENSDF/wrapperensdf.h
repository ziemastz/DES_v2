#ifndef WRAPPERENSDF_H
#define WRAPPERENSDF_H
/******************************************************************************
 * Library name:        WrapperENSDF
 * Author:              Tomasz Ziemek, POLATOM, Poland
 * Date:                16.01.2023
 * Qt version:          5.15.2
 *
 * Description:         Library for reading nuclear data contained in ENSDF
 *                      files.
 * Version:             1.0.1
 *
 * Change log
 *  1.0.1:
 *          - Loading data only from the first records without continuation
 *            records.
 *          - Records related to radionuclide decay are read.
 *          - Records with references, comments, etc. are omitted.
 *
 *
 ******************************************************************************
 */
#include "WrapperENSDF_global.h"
#include "ensdf.h"
#include "recordensdf.h"

class WRAPPERENSDF_EXPORT WrapperENSDF
{
public:
    WrapperENSDF(const QString &filename);

    bool read();

    QString getParent() const;
    QString getParent(const int &noDaughter) const;

    QString getHalfLifeValueParent(const int &noDaughter) const;
    QString getHalfLifeUncertaintyParent(const int &noDaughter) const;
    QString getHalfLifeUnitParent(const int &noDaughter) const;

    QString getSpinParityParent(const int &noDaughter) const;

    int countDaughters() const;
    QString getDaughter(const int &noDaughter) const;
    QString getHalfLifeValueDaughter(const int &noDaughter) const;
    QString getHalfLifeUncertaintyDaughter(const int &noDaughter) const;
    QString getHalfLifeUnitDaughter(const int &noDaughter) const;

    int countLevels(const int &noDaughter) const;
    QString getLevelEnergy(const int &noDaughter, const int &noLevel) const;
    QString getHalfLifeValueLevel(const int &noDaughter, const int &noLevel) const;
    QString getHalfLifeUncertaintyLevel(const int &noDaughter, const int &noLevel) const;
    QString getHalfLifeUnitLevel(const int &noDaughter, const int &noLevel) const;

    bool findBeta(const int &noDaughter, const int &noLevel) const;
    QString getIntensityBeta(const int &noDaughter, const int &noLevel) const;

    bool findAlpha(const int &noDaughter, const int &noLevel) const;
    QString getIntensityAlpha(const int &noDaughter, const int &noLevel) const;

    bool findEC(const int &noDaughter, const int &noLevel) const;
    QString getIntensityEC(const int &noDaughter, const int &noLevel) const;
    QString getIntensityBetaPlus(const int &noDaughter, const int &noLevel) const;
    QString getIntensityTotalEC(const int &noDaughter, const int &noLevel) const;

    int countGammas(const int &noDaughter, const int &noLevel) const;
    QString getGammaEnergy(const int &noDaughter, const int &noLevel, const int &noGamma) const;
    QString getGammaIntensity(const int &noDaughter, const int &noLevel, const int &noGamma) const;
    QString getGammaMultipolarity(const int &noDaughter, const int &noLevel, const int &noGamma) const;
    QString getGammaTotalElectronConvertion(const int &noDaughter, const int &noLevel, const int &noGamma) const;
    QString getFinalLevelEnergy(const int &noDaughter, const int &noLevel, const int &noGamma) const;

private:
    QVector<ENSDF> raw;

    QString _filename;
    int count_line;
    bool wrap(const RecordENSDF &line);
    bool isBlank(const RecordENSDF &str) const;
    bool isBlank(const QString &str) const;

};

#endif // WRAPPERENSDF_H
