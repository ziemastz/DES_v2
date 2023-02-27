#include "decaysimulator.h"
#include "Decay/cesimulation.h"
#include "qdebug.h"
#include "Decay/datavector.h"
#include <cmath>
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
    convertToNS["y"] =  3.1556925974592E+16;
    convertToNS["d"] =  8.64E+13;
    convertToNS["h"] =  3.6E+12;
    convertToNS["min"]= 6E+10;
    convertToNS["s"] =  1E+09;
    convertToNS["ms"] = 1E+06;
    convertToNS["μs"] = 1E+03;
    convertToNS["ns"] = 1E+00;
    convertToNS["ps"] = 1E-03;
    convertToNS["fs"] = 1E-06;
    convertToNS["as"] = 1E-09;
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
    //contenery - open file to write
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
        QVector<QStringList> secendary(3);
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
            if(branch.level.halfLifeValue > 0. && reslovingTime > 0. && deadTime >0.) {
                double l_t12 = branch.level.halfLifeValue*convertToNS.value(branch.level.halfLifeUnit);

                double p_rt = 1-exp(-log(2)*(reslovingTime/l_t12));
                double p_dt = exp(-log(2)*(deadTime*1000/l_t12));

                DataVector rt;
                rt.put(1,p_rt);
                rt.put(0,1-p_rt);
                if((int)rt.random()) {
                    DataVector p_ce;
                    p_ce.put(0,branch.gammes.at(index).intensity);
                    p_ce.put(1,p_g.at(index)-branch.gammes.at(index).intensity);
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
                }else {
                    DataVector dt;
                    dt.put(1,p_dt);
                    dt.put(0,1-p_dt);
                    if((int)dt.random()) {
                        DataVector p_ce;
                        p_ce.put(0,branch.gammes.at(index).intensity);
                        p_ce.put(1,p_g.at(index)-branch.gammes.at(index).intensity);
                        if((int)p_ce.random()) {
                            //CE
                            ceSim.setGamma(branch.gammes.at(index));
                            ceSim.loadAtomicData();
                            ceSim.start();

                            foreach (double energy, ceSim.getEmittedElectrons()) {
                               secendary[0] << QString::number(energy);
                            }
                            foreach (double energy, ceSim.getEmittedXRay()) {
                                secendary[1] << QString::number(energy);
                            }
                            foreach (QString tag, ceSim.getTagEmitted()) {
                               secendary[2] <<  tag;
                            }

                        }else {
                                //gamma
                            secendary[1] << QString::number(branch.gammes.at(index).energy);
                            secendary[2] << "G";
                        }
                    }
                }

            }else {
                DataVector p_ce;
                p_ce.put(0,branch.gammes.at(index).intensity);
                p_ce.put(1,p_g.at(index)-branch.gammes.at(index).intensity);
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
            for(int i = 0; i < decay.branches.size();i++) {
                if(decay.branches.at(i).level.excited_level_keV == final_level)
                    branch = decay.branches.at(i);
            }

            }

        }
        *outElectron << "\n";
        *outGamma << "\n";
        *outTag << "\n";
        if(!secendary.at(2).isEmpty()) { // after dead time decay record by counter as secendary chain
            *outElectron << currentDecay<<"\t"<<secendary.at(0).join("\t")<<"\n";
            *outGamma << currentDecay<<"\t"<<secendary.at(1).join("\t") << "\n";
            *outTag << currentDecay<<"\t"<<secendary.at(2).join("\t")<< "\n";
        }


    }
    qInfo() << "Simulation time: "<< timer.elapsed() << " ms";
    return true;
}

void DecaySimulator::ElectronsConfiguration()
{

}
