#ifndef BETADATA_H
#define BETADATA_H

#include <QObject>

class BetaData
{
public:
    BetaData();
    bool load(const QString &record);
    int level;
private:
    QString nucid;
    QString blank;
    QString multiple;
    double endpointEnergy;
    double uncerEndpointEnergy;
    double intensity;
    double uncerIntensity;
    double logFT;
    double uncerLogFT;
    QString commentFlag;
    QString forbiddenness;
    QString Q;
};

#endif // BETADATA_H
