#ifndef ALPHA_H
#define ALPHA_H

#include <QObject>

class Alpha
{
public:
    Alpha();
    bool load(const QString &record);

private:
    QString nucid;
    QString blank;
    QString multiple;
    double energy;
    double uncerEnergy;
    double intensity;
    double uncerIntensity;
    double hindranceFactor;
    double uncerHindranceFactor;
    QString commentFlag;
    QString Q;
};

#endif // ALPHA_H
