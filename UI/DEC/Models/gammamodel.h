#ifndef GAMMAMODEL_H
#define GAMMAMODEL_H

#include <QMap>
#include <QString>
class GammaModel
{
public:
    QString nuclide;
    double initialLevel_keV;
    double finalLevel_keV;
    double energy;
    double intensity;
    QString multipolarity;
    double total_internal_conversion;
    QMap<QString,double> conversion_electrons; //Subshell, Yield

};

#endif // GAMMAMODEL_H
