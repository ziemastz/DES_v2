#include "decaysimulator.h"
#include "qdebug.h"

DecaySimulator::DecaySimulator(const DecaySchemeModel &decayScheme, const uint &setDecayEvents, const double &setResolvingTime, const double &setDeadTime) :
    decay(decayScheme),
    decayEvents(setDecayEvents),
    reslovingTime(setResolvingTime),
    deadTime(setDeadTime)
{
    currentDecay = 0;
    outElectron = nullptr;
    outGamma = nullptr;
}

DecaySimulator::~DecaySimulator()
{
    if(outElectron != nullptr) {
        delete outElectron;
        fElectrons.close();
    }
    if(outGamma != nullptr) {
        delete outGamma;
        fGammas.close();
    }
}

bool DecaySimulator::start()
{
    //contenery
    fElectrons.setFileName("emittedElectrons_"+decay.radionuclide+".txt");
    fGammas.setFileName("emittedGammas_"+decay.radionuclide+".txt");
    if(!fElectrons.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Creating error "
                   << fElectrons.fileName()
                   << " : " <<fElectrons.errorString();
        return false;
    }

    if(!fGammas.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Creating error "
                   << fGammas.fileName()
                   << " : " <<fGammas.errorString();
        return false;
    }

    outElectron = new QTextStream(&fElectrons);
    outGamma = new QTextStream(&fElectrons);




    return true;
}

void DecaySimulator::ElectronsConfiguration()
{

}
