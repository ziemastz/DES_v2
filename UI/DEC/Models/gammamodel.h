#ifndef GAMMAMODEL_H
#define GAMMAMODEL_H

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

};

#endif // GAMMAMODEL_H
