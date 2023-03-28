#ifndef ECMODEL_H
#define ECMODEL_H

#include <QString>
#include <QVector>
#include <QMap>
#include "Models/betatransitionmodel.h"

class ECModel
{
public:
    ECModel();
    uint idBranch;
    double intensityEC;
    double intensityBetaPlus;
    BetaTransitionModel betaPlus;
    QMap<QString,double> subshell_probability;


};

#endif // ECMODEL_H
