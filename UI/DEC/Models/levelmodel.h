#ifndef LEVELMODEL_H
#define LEVELMODEL_H

#include <QString>

class LevelModel
{
public:
   double excited_level_keV;

   double halfLifeValue;
   double halfLifeUncertainty;
   QString halfLifeUnit;

   QString spinParity;
};

#endif // LEVELMODEL_H
