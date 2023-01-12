#ifndef EC_H
#define EC_H

#include <QObject>

class EC
{
public:
    EC();
    bool load(const QString &record);

private:
    QString nucid;
    QString blank;
    QString multiple;
    double energy;
    double uncerEnergy;
    double intensityBeta;
    double uncerIntensityBeta;
    double intensityEC;
    double uncerIntensityEC;
    double logFT;
    double uncerLogFT;
    double intensityTotal;
    double uncerIntensityTotal;
    QString commentFlag;
    QString forbiddenness;
    QString Q;

};

#endif // EC_H
