#include "decaysimulator.h"
#include "Decay/cesimulation.h"
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
    CESimulation ceSim;
    QElapsedTimer timer;
    timer.start();
    while(decayEvents >= ++currentDecay) {
        //qDebug() << "Event: "<<currentDecay;
        BranchModel branch = decay.branches.at((int)p_branches.random());
        *outElectron << currentDecay;
        *outGamma << currentDecay;
        *outTag << currentDecay;

        if(branch.transition == "EC") {
            //qDebug() << "Transition EC";
            ecSim.setBranch(branch);
            ecSim.loadAtomicData();
            ecSim.start();

            foreach (double energy, ecSim.getEmittedElectrons()) {
                *outElectron << "\t" << energy;
            }
            foreach (double energy, ecSim.getEmittedXRay()) {
                *outGamma << "\t" << energy;
            }
            foreach (QString tag, ecSim.getTagEmitted()) {
                *outTag << "\t" << tag;
            }

        }

        //gamma emisions
        if(!branch.gammes.isEmpty()) {
        double final_level = -1;
        while(final_level != 0.0) {
            DataVector p_g;
            for (int i = 0; i < branch.gammes.size(); i++) {
                double total_g_ce = branch.gammes.at(i).total_internal_conversion
                                  * branch.gammes.at(i).intensity
                                  + branch.gammes.at(i).intensity;
                p_g.put(i,total_g_ce);
            }
            int index = (int)p_g.random();
            final_level = branch.gammes.at(index).finalLevel_keV;
            DataVector p_ce;
            p_ce.put(0,1-branch.gammes.at(index).total_internal_conversion);
            p_ce.put(1,branch.gammes.at(index).total_internal_conversion);
            if((int)p_ce.random()) {
                //CE
                ceSim.setGamma(branch.gammes.at(index));
                ceSim.loadAtomicData();
                ceSim.start();

                foreach (double energy, ceSim.getEmittedElectrons()) {
                    *outElectron << "\t" << energy;
                }
                foreach (double energy, ceSim.getEmittedXRay()) {
                    *outGamma << "\t" << energy;
                }
                foreach (QString tag, ceSim.getTagEmitted()) {
                    *outTag << "\t" << tag;
                }

            }else {
                //gamma
                *outGamma << "\t" << branch.gammes.at(index).energy;
                *outTag << "\t" << "G";
            }
        }
        }
        *outElectron << "\n";
        *outGamma << "\n";
        *outTag << "\n";
    }
    qInfo() << "Simulation time: "<< timer.elapsed() << " ms";
    return true;
}

void DecaySimulator::ElectronsConfiguration()
{

}
