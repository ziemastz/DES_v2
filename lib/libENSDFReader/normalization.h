#ifndef NORMALIZATION_H
#define NORMALIZATION_H
#include <QObject>

class NormalizationData
{
public:
    NormalizationData();
    bool load(const QString &record);
private:
    QString nucid;
    QString blank;
    QString multiple;
    double photon;
    double uncerPhoton;
    double transition;
    double uncerTransition;
    double branchingRatio;
    double uncerBranchingRatio;
    double branch ;
    double uncerBranch ;
    double delayed ;
    double uncerDelayed;
};

#endif // NORMALIZATION_H
