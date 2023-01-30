#ifndef ECMODEL_H
#define ECMODEL_H

#include <QString>
#include <QVector>
#include <QMap>
class ECModel
{
public:
    uint idBranch;
    double intensityEC;
    double intensityBetaPlus;
    QMap<QString,double> subshell_probability;


};

#endif // ECMODEL_H
