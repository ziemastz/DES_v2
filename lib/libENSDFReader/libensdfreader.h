#ifndef LIBENSDFREADER_H
#define LIBENSDFREADER_H
#include <QObject>
#include "ensdfdata.h"

class LibENSDFReader
{
public:
    LibENSDFReader();
    void load(const QString &fileName);

private:
    enum RecordType {
        Identification = 0,
        History,
        QValue,
        CrossReference,
        Comment,
        Parent,
        Normalization,
        ProductionNormalization,
        Level,
        Beta,
        EC,
        Alpha,
        DelayedParticle,
        Gamma,
        Reference,
        End,
        Empty
    };

    RecordType specifyRecord(const QString &record);

    void addNuclide();
    QVector<ENSDFData> _data;
    int currentNuclide;

    void addIdentification(const QString &record);
    void addParent(const QString &record);
    void addNormalization(const QString &record);
    void addLevel(const QString &record);
    void addBeta(const QString &record);

};

#endif // LIBENSDFREADER_H
