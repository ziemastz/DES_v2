#ifndef CESIMULATION_H
#define CESIMULATION_H
#include "Models/gammamodel.h"
#include "Controllers/atomicdatacontroller.h"


class CESimulation
{
public:
    enum TRANSITIONS
    {
        Auger = 0,
        Xray,
        C_KL1L2,
        C_KL1L3,
        C_KL2L3
    };
    CESimulation();
    void loadAtomicData();
    void setGamma(const GammaModel &newGamma);
    void start();

    QVector<double> getEmittedElectrons() const;
    QVector<double> getEmittedXRay() const;
    QStringList getTagEmitted() const;

private:
    GammaModel gamma;
    AtomicDataModel atomicData;

    QVector<double> emittedElectrons;
    QVector<double> emittedXRay;
    QStringList tagEmitted;

    void ElectronConfiguration();
    QString ConversionElectron();

    TRANSITIONS Transition(const QString &subshell);
    QString AugerEmissions(const QString &subshell);
    double ElectronEnergy(const QString &vacancy, const QString &occupancy, const QString &emitting);

    QString XRayEmissions(const QString &subshell);
    double XRayEnergy(const QString &vacancy, const QString &occupancy);

    QString CosterKronigEmissions(const QString &subshell, const QString &occupancy);
};

#endif // CESIMULATION_H
