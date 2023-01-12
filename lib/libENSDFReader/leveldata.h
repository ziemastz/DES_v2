#ifndef LEVELDATA_H
#define LEVELDATA_H
#include <QObject>

class LevelData
{
public:
    LevelData();
    bool load(const QString &record);
private:
    QString nucid;
    QString blank;
    QString multiple;
    double energy;
    double uncerEnergy;
    QString spinParity;
    QString halfLife;
    QString uncerHalfLife;
    QString angularMomentum;
    QString spectroscopicStrenght;
    QString uncerSpectroscopicStrenght;
    QString commentFlag;
    QString metastableState;
    QString Q;
};

#endif // LEVELDATA_H
