#ifndef ECSIMULATION_H
#define ECSIMULATION_H
#include "Models/branchmodel.h"
#include "Controllers/atomicdatacontroller.h"

class ECSimulation
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
    ECSimulation(const BranchModel &branch);
    void start();

    QVector<double> getEmittedElectrons() const;

    QVector<double> getEmittedXRay() const;

private:
    BranchModel _branch;
    AtomicDataModel atomicData;
    void ElectronConfiguration();

    QString ElectronCapture();

    TRANSITIONS Transition(const QString &subshell);

    QString AugerEmissions(const QString &subshell);
    double ElectronEnergy(const QString &vacancy, const QString &occupancy, const QString &emitting);

    QString XRayEmissions(const QString &subshell);
    double XRayEnergy(const QString &vacancy, const QString &occupancy);

    QString CosterKronigEmissions(const QString &subshell, const QString &occupancy);

    QVector<double> emittedElectrons;
    QVector<double> emittedXRay;
};

#endif // ECSIMULATION_H
