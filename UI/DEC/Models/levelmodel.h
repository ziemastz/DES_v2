#ifndef LEVELMODEL_H
#define LEVELMODEL_H

#include <QString>

class LevelModel
{
public:
   QString excited_level_keV;

   QString halfLifeValue;
   QString halfLifeUncertainty;
   QString halfLifeUnit;

   QString spinParity;
};

#endif // LEVELMODEL_H
