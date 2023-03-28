#include "ecsimulation.h"
#include "Decay/datavector.h"

ECSimulation::ECSimulation(const BranchModel &branch) :
    _branch(branch)
{
    _branch = branch;
}

void ECSimulation::loadAtomicData()
{
    if(atomicData.nuclide != _branch.daughter.symbol) {
        AtomicDataController atomicContr;
        atomicData = atomicContr.getAtomicData(_branch.daughter.symbol);
    }
}

void ECSimulation::start()
{
    emittedElectrons.clear();
    emittedXRay.clear();
    tagEmitted.clear();

    //EC or beta+
    if(isBetaPlus()) {
        qDebug() << "Beta+ transition";
        betaPlus.setBranch(_branch);
        emittedElectrons << betaPlus.start();
        tagEmitted << "Beta+";
        return;
    }

    QVector<QString> vacancies;
    ElectronConfiguration();



    QString ec = ElectronCapture();

    if(ec.isEmpty()) {
        qWarning() << "No electron capture!";
        return;
    }

    vacancies << ec;

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

void ECSimulation::ElectronConfiguration()
{
    QStringList keys = atomicData.subshells.keys();
    foreach (QString subshell, keys) {
        atomicData.subshells[subshell].availablelElectrons =  atomicData.subshells[subshell].elektrons_max;
    }
}

bool ECSimulation::isBetaPlus()
{
    DataVector p_beta;
    p_beta.put(0,_branch.ec.intensityEC);
    p_beta.put(1,_branch.ec.intensityBetaPlus);
    if(p_beta.random() == 1)
        return true;
    else
        return false;
}

QString ECSimulation::ElectronCapture()
{
    QString ret;

    QStringList keys = _branch.ec.subshell_probability.keys();
    if(keys.size() == 0)
        return ret;

    DataVector p_ec;
    for(int i=0;i<keys.size();i++) {
        p_ec.put(i, _branch.ec.subshell_probability[keys.at(i)]);
    }
    int index = (int)p_ec.random();
    if(index == -1)
        return ret;

    ret = keys.at(index);
    if(!atomicData.subshells.contains(ret))
        return QString();

    atomicData.subshells[ret].availablelElectrons--;
    return ret;
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

double ECSimulation::ElectronEnergy(const QString &vacancy, const QString &occupancy, const QString &emitting)
{
    double Ev = atomicData.subshells.value(vacancy).binding_energy_eV;
    double Eo = atomicData.subshells.value(occupancy).binding_energy_eV;
    double Ee = atomicData.subshells.value(emitting).binding_energy_eV;
    return Ev - Eo - Ee;
}

QString ECSimulation::XRayEmissions(const QString &subshell)
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

double ECSimulation::XRayEnergy(const QString &vacancy, const QString &occupancy)
{
    double Ev = atomicData.subshells.value(vacancy).binding_energy_eV;
    double Eo = atomicData.subshells.value(occupancy).binding_energy_eV;
    return Ev - Eo;
}

QString ECSimulation::CosterKronigEmissions(const QString &subshell, const QString &occupancy)
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

QStringList ECSimulation::getTagEmitted() const
{
    return tagEmitted;
}

QVector<double> ECSimulation::getEmittedXRay() const
{
    return emittedXRay;
}

void ECSimulation::setBranch(const BranchModel &newBranch)
{
    _branch = newBranch;
}

QVector<double> ECSimulation::getEmittedElectrons() const
{
    return emittedElectrons;
}
