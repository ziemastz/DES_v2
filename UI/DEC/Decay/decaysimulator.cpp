#include "decaysimulator.h"
#include "qdebug.h"
#include "Decay/datavector.h"
#include <QElapsedTimer>
DecaySimulator::DecaySimulator(const DecaySchemeModel &decayScheme, const uint &setDecayEvents, const double &setResolvingTime, const double &setDeadTime) :
    decay(decayScheme),
    decayEvents(setDecayEvents),
    reslovingTime(setResolvingTime),
    deadTime(setDeadTime)
{
    currentDecay = 0;
    outElectron = nullptr;
    outGamma = nullptr;
    outTag = nullptr;
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
    if(outTag != nullptr) {
        delete outTag;
        fTag.close();
    }
}

bool DecaySimulator::start()
{
    //contenery
    fElectrons.setFileName(decay.radionuclide+"_emittedElectrons.txt");
    fGammas.setFileName(decay.radionuclide+"_emittedGammas.txt");
    fTag.setFileName(decay.radionuclide+"_Tags.txt");

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

    if(!fTag.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Creating error "
                   << fTag.fileName()
                   << " : " <<fTag.errorString();
        return false;
    }

    outElectron = new QTextStream(&fElectrons);
    outGamma = new QTextStream(&fGammas);
    outTag = new QTextStream(&fTag);

    //histogram of probability of branch
    DataVector p_branches;
    for(int i=0; i<decay.branches.size();i++) {
        p_branches.put(i,decay.branches.at(i).intensity);
    }

    // loop of decays
    ECSimulation ecSim;
    QElapsedTimer timer;
    timer.start();
    while(decayEvents >= ++currentDecay) {
        //qDebug() << "Event: "<<currentDecay;
        BranchModel branch = decay.branches.at((int)p_branches.random());

        if(branch.transition == "EC") {
            //qDebug() << "Transition EC";
            ecSim.setBranch(branch);
            ecSim.loadAtomicData();
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

            *outTag << currentDecay;
            foreach (QString tag, ecSim.getTagEmitted()) {
                *outTag << "\t" << tag;
            }
            *outTag << "\n";
        }

        //gamma emisions
        if(!branch.gammes.isEmpty()) {
        double final_level = -1;
        //while(final_level != 0.0) {

       // }
        }
    }
    qInfo() << "Simulation time: "<< timer.elapsed() << " ms";
    return true;
}

void DecaySimulator::ElectronsConfiguration()
{

}
