#ifndef DECAYSIMULATOR_H
#define DECAYSIMULATOR_H

#include <QObject>
#include <QTextStream>
#include <QFile>

#include "Models/decayschememodel.h"
class DecaySimulator
{
public:
    DecaySimulator(const DecaySchemeModel &decayScheme, const uint &setDecayEvents, const double &setResolvingTime = 0, const double &setDeadTime = 0);
    ~DecaySimulator();
 public slots:
    bool start();

private:
    DecaySchemeModel decay;
    uint decayEvents;
    double reslovingTime; // unit ns;
    double deadTime; // unit us;

    uint currentDecay;
    QStringList emittedElectrons;
    QStringList emittedGammas;

    QFile fElectrons;
    QFile fGammas;
    QTextStream *outElectron;
    QTextStream *outGamma;


    void ElectronsConfiguration();
};

#endif // DECAYSIMULATOR_H
