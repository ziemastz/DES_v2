#include "ecsimulation.h"
#include "Decay/datavector.h"



ECSimulation::ECSimulation(const BranchModel &branch) :
    _branch(branch)
{
    AtomicDataController atomicContr;
    atomicData = atomicContr.getAtomicData(_branch.daughter.symbol);
}

void ECSimulation::start()
{
    QVector<QString> vacancies;
    ElectronConfiguration();

    vacancies << ElectronCapture();

    while(!vacancies.isEmpty()) {
        QString index = vacancies.last();
        vacancies.removeLast();

        switch(Transition(index)) {

        case Auger:
        {
            QStringList augerTransition = AugerEmissions(index).split(QRegExp("\\s+"));
            vacancies << augerTransition.last() << augerTransition.first();
            emittedElectrons << ElectronEnergy(index,augerTransition.first(),augerTransition.last());
            break;
        }
        case Xray:
        {
            vacancies << XRayEmissions(index);
            emittedXRay << XRayEnergy(index,vacancies.last());
            break;
        }
        case C_KL1L2:
        {
            QString emitting = CosterKronigEmissions(index,"L2");
            vacancies << emitting
                      << "L2";
            emittedElectrons << ElectronEnergy(index,"L2",emitting);
            break;
        }
        case C_KL1L3:
        {
            QString emitting = CosterKronigEmissions(index,"L3");
            vacancies << emitting
                      << "L3";
            emittedElectrons << ElectronEnergy(index,"L3",emitting);
            break;
        }
        case C_KL2L3:
        {
            QString emitting = CosterKronigEmissions(index,"L3");
            vacancies << emitting
                      << "L3";
            emittedElectrons << ElectronEnergy(index,"L3",emitting);
            break;
        }
        default:
        {
            qWarning() << "Wrong random transistions: " << trans;
            break;
        }
        }
    }
}

void ECSimulation::ElectronConfiguration()
{
    QStringList keys = atomicData.subshells.keys();
    foreach (QString subshell, keys) {
        atomicData.subshells[subshell].availablelElectrons =  atomicData.subshells[subshell].elektrons_max;
    }
}

QString ECSimulation::ElectronCapture()
{
    DataVector p_ec;
    QStringList keys = _branch.ec.subshell_probability.keys();
    for(int i=0;i<keys.size();i++) {
        p_ec.put(i, _branch.ec.subshell_probability[keys.at(i)]);
    }
    return keys.at((int)p_ec.random());
}

ECSimulation::TRANSITIONS ECSimulation::Transition(const QString &subshell)
{
    double f12 = 0;
    double f13 = 0;
    double f23 = 0;

    if(subshell == "L1") {
        f12 = atomicData.f12;
        f13 = atomicData.f13;
    }
    if(subshell == "L2") {
        f23 = atomicData.f23;
    }
    double w = atomicData.fluorescenceYields[subshell];
    double a = 1 - w - f12 -f13 - f23;

    DataVector p_trans;
    p_trans.put(0,a);
    p_trans.put(1,w);
    if(f12 > 0.0)
        p_trans.put(2,f12);
    if(f13 > 0.0)
        p_trans.put(3,f13);
    if(f23 > 0.0)
        p_trans.put(4,f23);

    return static_cast<TRANSITIONS>(p_trans.random());
}

QString ECSimulation::AugerEmissions(const QString &subshell)
{
    QStringList keys = atomicData.subshells[subshell].auger.keys();
    DataVector p_auger;
    for(int i=0; i<keys.size(); i++) {
        double intensity = atomicData.subshells[subshell].auger[keys.at(i)];
        if(intensity > 0.0 && atomicData.subshells[keys.at(i).split(QRegExp("\\s++")).last()].availablelElectrons > 0)
            p_auger.put(i,intensity);
    }
    QString ret = keys.at((int)p_auger.random());
    atomicData.subshells[ret.split(QRegExp("\\s++")).last()].availablelElectrons--;
    return ret;
}

double ECSimulation::ElectronEnergy(const QString &vacancy, const QString &occupancy, const QString &emitting)
{
    double Ev = atomicData.subshells[vacancy].binding_energy_keV;
    double Eo = atomicData.subshells[occupancy].binding_energy_keV;
    double Ee = atomicData.subshells[emitting].binding_energy_keV;
    return Ev - Eo - Ee;
}

QString ECSimulation::XRayEmissions(const QString &subshell)
{
    QStringList keys = atomicData.subshells[subshell].xRay.keys();
    DataVector p_xRay;
    for(int i=0; i<keys.size(); i++) {
        double intensity = atomicData.subshells[subshell].xRay[keys.at(i)];
        if(intensity > 0.0 && atomicData.subshells[keys.at(i)].availablelElectrons > 0)
            p_xRay.put(i,intensity);
    }
    QString ret = keys.at((int)p_xRay.random());
    atomicData.subshells[ret].availablelElectrons--;
    return ret;
}

double ECSimulation::XRayEnergy(const QString &vacancy, const QString &occupancy)
{
    double Ev = atomicData.subshells[vacancy].binding_energy_keV;
    double Eo = atomicData.subshells[occupancy].binding_energy_keV;
    return Ev - Eo;
}

QString ECSimulation::CosterKronigEmissions(const QString &subshell, const QString &occupancy)
{
    QStringList keys = atomicData.subshells[subshell].auger.keys();
    DataVector p_auger;
    for(int i=0; i<keys.size(); i++) {
        QStringList transitions = keys.at(i).split(QRegExp("\\s+"));
        double intensity = atomicData.subshells[subshell].auger[keys.at(i)];
        if(intensity > 0.0 &&
           transitions.first() == occupancy &&
           atomicData.subshells[transitions.last()].availablelElectrons > 0) {

            p_auger.put(i,intensity);
        }
    }
    QString ret = keys.at((int)p_auger.random()).split(QRegExp("\\s++")).last();
    atomicData.subshells[ret].availablelElectrons--;
    return ret;
}

QVector<double> ECSimulation::getEmittedXRay() const
{
    return emittedXRay;
}

QVector<double> ECSimulation::getEmittedElectrons() const
{
    return emittedElectrons;
}
