#ifndef ECMODEL_H
#define ECMODEL_H

#include <QString>
#include <QVector>
#include <QMap>
class ECModel
{
public:
    QString intensityEC;
    QString intensityBetaPlus;
    QVector<QString> subshell;
    QVector<QString> probability;
    QMap<QString,QString> subshell_probability;


};

#endif // ECMODEL_H
