#ifndef ATOMICSUBSHELLMODEL_H
#define ATOMICSUBSHELLMODEL_H

#include <QString>
#include <QMap>
#include <QStringList>
class AtomicSubshellModel
{
public:
    AtomicSubshellModel();
    AtomicSubshellModel& operator =(const AtomicSubshellModel &other);
    double binding_energy_keV;
    int elektrons_max;
    int availablelElectrons;

    QMap<QString,double> auger;
    QMap<QString,double> xRay;

    QStringList getSubshells() const;
    QStringList getSubshells(const QString &fromSubshell) const;

private:
    const QStringList subshells = QStringList() << "K"

                                                << "L1"
                                                << "L2"
                                                << "L3"

                                                << "M1"
                                                << "M2"
                                                << "M3"
                                                << "M4"
                                                << "M5"

                                                << "N1"
                                                << "N2"
                                                << "N3"
                                                << "N4"
                                                << "N5"
                                                << "N6"
                                                << "N7"

                                                << "O1"
                                                << "O2"
                                                << "O3"
                                                << "O4"
                                                << "O5"
                                                << "O6"
                                                << "O7"

                                                << "P1"
                                                << "P2"
                                                << "P3"
                                                << "P4"
                                                << "P5"

                                                << "Q1";
};

#endif // ATOMICSUBSHELLMODEL_H
