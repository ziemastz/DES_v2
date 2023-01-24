#ifndef ATOMICSUBSHELLMODEL_H
#define ATOMICSUBSHELLMODEL_H

#include <QString>
#include <QMap>

class AtomicSubshellModel
{
public:
    QString binding_energy_keV;
    QString elektrons_max;
    QMap<QString,QString> auger;
    QMap<QString,QString> xRay;

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
