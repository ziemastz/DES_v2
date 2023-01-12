#ifndef PARENTDATA_H
#define PARENTDATA_H
#include <QObject>

class ParentData
{
public:
    ParentData();
    bool load(const QString &record);

private:
    QString nucid;
    QString blank;
    QString multiple;
    double energy; // in keV; (0.0 for g.s.)
    double uncerEnergy;
    QString spinParity;
    QString halfLife;
    double uncerHalfLife;
    double QValue;   // in keV (total energy avaiable for g.s->g.s. transition)
    double uncerQValue ;
    QString ionizationState;
};

#endif // PARENTDATA_H
