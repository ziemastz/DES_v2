#ifndef PARENTRECORD_H
#define PARENTRECORD_H
#include <QString>

class ParentRecord
{
public:
    ParentRecord();
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

    QString getQp() const;
    void setQp(const QString &newQp);

    QString getDqp() const;
    void setDqp(const QString &newDqp);

    QString getIon() const;
    void setIon(const QString &newIon);

private:
    QString blank;

    QString nucid;
    QString e;
    QString de;
    QString j;
    QString t;
    QString dt;
    QString qp;
    QString dqp;
    QString ion;

};

#endif // PARENTRECORD_H
