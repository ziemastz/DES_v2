#include "decaysimulator.h"
#include "qdebug.h"
#include "Decay/datavector.h"

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

    //histogram of probability of branch
    DataVector p_branches;
    for(int i=0; i<decay.branches.size();i++) {
        p_branches.put(i,decay.branches.at(i).intensity);
    }

    // loop of decays
    while(decayEvents >= ++currentDecay) {
        BranchModel branch = decay.branches.at((int)p_branches.random());

        if(branch.transition == "EC") {
            ECSimulation ecSim(branch);
            ecSim.start();

            *outElectron << currentDecay;
            foreach (double energy, ecSim.getEmittedElectrons()) {
                *outElectron << "\t" << energy;
            }
            *outElectron << "\n";

            *outGamma << currentDecay;
            foreach (double energy, ecSim.getEmittedXRay()) {
                *outGamma << "\t" << energy;
            }
            *outGamma << "\n";
        }

        //gamma emisions
        if(!branch.gammes.isEmpty()) {

        }
    }

    return true;
}

void DecaySimulator::ElectronsConfiguration()
{

}
