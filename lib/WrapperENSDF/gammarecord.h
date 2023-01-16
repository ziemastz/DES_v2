#ifndef GAMMARECORD_H
#define GAMMARECORD_H
#include <QString>

class GammaRecord
{
public:
    GammaRecord();
    QString getBlank() const;
    void setBlank(const QString &newBlank);

    QString getNucid() const;
    void setNucid(const QString &newNucid);

    QString getE() const;
    void setE(const QString &newE);

    QString getDe() const;
    void setDe(const QString &newDe);

    QString getRi() const;
    void setRi(const QString &newRi);

    QString getDri() const;
    void setDri(const QString &newDri);

    QString getM() const;
    void setM(const QString &newM);

    QString getMr() const;
    void setMr(const QString &newMr);

    QString getDmr() const;
    void setDmr(const QString &newDmr);

    QString getCc() const;
    void setCc(const QString &newCc);

    QString getDcc() const;
    void setDcc(const QString &newDcc);

    QString getTi() const;
    void setTi(const QString &newTi);

    QString getDti() const;
    void setDti(const QString &newDti);

    QString getC() const;
    void setC(const QString &newC);

    QString getCoin() const;
    void setCoin(const QString &newCoin);

    QString getQ() const;
    void setQ(const QString &newQ);

private:
    QString blank;
    QString nucid;
    QString e;
    QString de;
    QString ri;
    QString dri;
    QString m;
    QString mr;
    QString dmr;
    QString cc;
    QString dcc;
    QString ti;
    QString dti;
    QString c;
    QString coin;
    QString q;
};

#endif // GAMMARECORD_H
