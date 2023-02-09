#include "cesimulation.h"
#include "Decay/datavector.h"

CESimulation::CESimulation()
{
    gamma = GammaModel();
}

void CESimulation::loadAtomicData()
{
    if(atomicData.nuclide != gamma.nuclide) {
        AtomicDataController atomicContr;
        atomicData = atomicContr.getAtomicData(gamma.nuclide);
    }
}

void CESimulation::setGamma(const GammaModel &newGamma)
{
    gamma = newGamma;
}

void CESimulation::start()
{
    QVector<QString> vacancies;
    ElectronConfiguration();

    emittedElectrons.clear();
    emittedXRay.clear();
    tagEmitted.clear();

    QString ce = ConversionElectron();

    if(ce.isEmpty()) {
        qWarning() << "No conversion electron!";
        return;
    }

    vacancies << ce;
    emittedElectrons << gamma.energy - (atomicData.subshells.value(ce).binding_energy_eV/1000);
    tagEmitted << "ce_"+ce;

    while(!vacancies.isEmpty()) {
        QString index = vacancies.last();
        vacancies.removeLast();

        switch(Transition(index)) {

        case Auger:
        {
            QString transition = AugerEmissions(index);
            if(transition.isEmpty())
                break;

            QStringList augerTransition = transition.split(QRegExp("\\s+"));
            vacancies << augerTransition.last() << augerTransition.first();
            emittedElectrons << ElectronEnergy(index,augerTransition.first(),augerTransition.last())/1000;
            tagEmitted << "A_"+augerTransition.last();
            break;
        }
        case Xray:
        {
            QString transition = XRayEmissions(index);
            if(transition.isEmpty())
                break;

            vacancies << transition;
            emittedXRay << XRayEnergy(index,transition)/1000; //unit keV
            tagEmitted << "X_"+transition;
            break;
        }
        case C_KL1L2:
        {
            QString emitting = CosterKronigEmissions(index,"L2");
            if(emitting.isEmpty())
                break;

            vacancies << emitting
                      << "L2";
            emittedElectrons << ElectronEnergy(index,"L2",emitting)/1000;
            tagEmitted << "C-Kf12_"+emitting;
            break;
        }
        case C_KL1L3:
        {
            QString emitting = CosterKronigEmissions(index,"L3");
            if(emitting.isEmpty())
                break;

            vacancies << emitting
                      << "L3";
            emittedElectrons << ElectronEnergy(index,"L3",emitting)/1000;
            tagEmitted << "C-Kf13_"+emitting;
            break;
        }
        case C_KL2L3:
        {
            QString emitting = CosterKronigEmissions(index,"L3");
            if(emitting.isEmpty())
                break;

            vacancies << emitting
                      << "L3";
            emittedElectrons << ElectronEnergy(index,"L3",emitting)/1000;
            tagEmitted << "C-Kf23_"+emitting;
            break;
        }
        default:
        {
            qWarning() << "Wrong random transistions: " << index;
            break;
        }
        }
    }
}

QString CESimulation::ConversionElectron()
{
    QString ret;

    QStringList keys = gamma.conversion_electrons.keys();
    if(keys.size() == 0)
        return ret;

    DataVector p_ce;
    for(int i=0;i<keys.size();i++) {
        p_ce.put(i, gamma.conversion_electrons.value(keys.at(i)));
    }
    int index = (int)p_ce.random();
    if(index == -1)
        return ret;

    ret = keys.at(index);
    if(!atomicData.subshells.contains(ret))
        return QString();

    atomicData.subshells[ret].availablelElectrons--;
    return ret;
}

CESimulation::TRANSITIONS CESimulation::Transition(const QString &subshell)
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

QString CESimulation::AugerEmissions(const QString &subshell)
{
    QString ret;
    if(!atomicData.subshells.contains(subshell))
        return ret;

    QStringList keys = atomicData.subshells.value(subshell).auger.keys();
    if(keys.size() == 0)
        return ret;

    DataVector p_auger;
    for(int i=0; i<keys.size(); i++) {
        double intensity = atomicData.subshells.value(subshell).auger.value(keys.at(i));
        int electron = atomicData.subshells.value(keys.at(i).split(QRegExp("\\s+")).last()).availablelElectrons;
        if(intensity > 0.0 && electron > 0)
            p_auger.put(i,intensity);
    }
    int index = (int)p_auger.random();
    if(index == -1)
        return ret;
    ret = keys.at(index);
    atomicData.subshells[ret.split(QRegExp("\\s+")).first()].availablelElectrons--;
    atomicData.subshells[ret.split(QRegExp("\\s+")).last()].availablelElectrons--;
    atomicData.subshells[subshell].availablelElectrons++;
    return ret;
}

double CESimulation::ElectronEnergy(const QString &vacancy, const QString &occupancy, const QString &emitting)
{
    double Ev = atomicData.subshells.value(vacancy).binding_energy_eV;
    double Eo = atomicData.subshells.value(occupancy).binding_energy_eV;
    double Ee = atomicData.subshells.value(emitting).binding_energy_eV;
    return Ev - Eo - Ee;
}

QString CESimulation::XRayEmissions(const QString &subshell)
{
    QString ret;
    if(!atomicData.subshells.contains(subshell))
        return ret;

    QStringList keys = atomicData.subshells.value(subshell).xRay.keys();
    if(keys.size() == 0)
        return ret;

    DataVector p_xRay;
    for(int i=0; i<keys.size(); i++) {
        double intensity = atomicData.subshells.value(subshell).xRay.value(keys.at(i));
        if(intensity > 0.0 && atomicData.subshells.value(keys.at(i)).availablelElectrons > 0)
            p_xRay.put(i,intensity);
    }
    int index = (int)p_xRay.random();
    if(index == -1)
        return ret;
    ret = keys.at(index);
    atomicData.subshells[ret].availablelElectrons--;
    atomicData.subshells[subshell].availablelElectrons++;
    return ret;
}

double CESimulation::XRayEnergy(const QString &vacancy, const QString &occupancy)
{
    double Ev = atomicData.subshells.value(vacancy).binding_energy_eV;
    double Eo = atomicData.subshells.value(occupancy).binding_energy_eV;
    return Ev - Eo;
}

QString CESimulation::CosterKronigEmissions(const QString &subshell, const QString &occupancy)
{
    QString ret;
    if(!atomicData.subshells.contains(subshell))
        return ret;

    QStringList keys = atomicData.subshells.value(subshell).auger.keys();
    if(keys.size() == 0)
        return ret;

    DataVector p_auger;
    for(int i=0; i<keys.size(); i++) {
        QStringList transitions = keys.at(i).split(QRegExp("\\s+"));
        double intensity = atomicData.subshells.value(subshell).auger.value(keys.at(i));
        if(intensity > 0.0 &&
           transitions.first() == occupancy &&
           atomicData.subshells.value(transitions.last()).availablelElectrons > 0) {

            p_auger.put(i,intensity);
        }
    }
    int index = (int)p_auger.random();
    if(index == -1)
        return ret;
    ret = keys.at(index).split(QRegExp("\\s+")).last();
    atomicData.subshells[ret].availablelElectrons--;
    return ret;
}

QStringList CESimulation::getTagEmitted() const
{
    return tagEmitted;
}

void CESimulation::ElectronConfiguration()
{
    QStringList keys = atomicData.subshells.keys();
    foreach (QString subshell, keys) {
        atomicData.subshells[subshell].availablelElectrons =  atomicData.subshells[subshell].elektrons_max;
    }
}

QVector<double> CESimulation::getEmittedXRay() const
{
    return emittedXRay;
}

QVector<double> CESimulation::getEmittedElectrons() const
{
    return emittedElectrons;
}
