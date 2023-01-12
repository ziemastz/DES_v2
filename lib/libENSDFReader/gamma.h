#ifndef GAMMA_H
#define GAMMA_H

#include <QObject>

class Gamma
{
public:
    Gamma();
    bool load(const QString &record);

private:
    QString nucid;
    QString blank;
    QString multiple;
    double energy;
    double uncerEnergy;
    double intensity;
    double uncerIntensity;
    QString multipolarity;
    QString mixingRatio;
    QString uncerMixingRatio;
    double conversionTotal;
    double uncerConversionTotal;
    double intensityTotal;
    double uncerIntensityTotal;
    QString commentFlag;
    QString coincidence;
    QString Q;
};

#endif // GAMMA_H
