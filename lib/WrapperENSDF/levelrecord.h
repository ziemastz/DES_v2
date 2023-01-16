#ifndef LEVELRECORD_H
#define LEVELRECORD_H

#include <QString>

class LevelRecord
{
public:
    LevelRecord();
    QString getBlank() const;
    void setBlank(const QString &newBlank);

    QString getNucid() const;

    void setNucid(const QString &newNucid);

    QString getE() const;
    void setE(const QString &newE);

    QString getDe() const;
    void setDe(const QString &newDe);

    QString getJ() const;
    void setJ(const QString &newJ);

    QString getT() const;
    void setT(const QString &newT);

    QString getDt() const;
    void setDt(const QString &newDt);

    QString getL() const;
    void setL(const QString &newL);

    QString getS() const;
    void setS(const QString &newS);

    QString getDs() const;
    void setDs(const QString &newDs);

    QString getC() const;
    void setC(const QString &newC);

    QString getMs() const;
    void setMs(const QString &newMs);

    QString getQ() const;
    void setQ(const QString &newQ);

private:
    QString blank;

    QString nucid;
    QString e;
    QString de;
    QString j;
    QString t;
    QString dt;
    QString l;
    QString s;
    QString ds;
    QString c;
    QString ms;
    QString q;
};

#endif // LEVELRECORD_H
