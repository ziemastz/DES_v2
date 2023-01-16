#ifndef BETARECORD_H
#define BETARECORD_H
#include <QString>

class BetaRecord
{
public:
    BetaRecord();
    QString getBlank() const;
    void setBlank(const QString &newBlank);

    QString getNucid() const;
    void setNucid(const QString &newNucid);

    QString getE() const;
    void setE(const QString &newE);

    QString getDe() const;
    void setDe(const QString &newDe);

    QString getIb() const;
    void setIb(const QString &newIb);

    QString getDib() const;
    void setDib(const QString &newDib);

    QString getLogft() const;
    void setLogft(const QString &newLogft);

    QString getDft() const;
    void setDft(const QString &newDft);

    QString getC() const;
    void setC(const QString &newC);

    QString getUn() const;
    void setUn(const QString &newUn);

    QString getQ() const;
    void setQ(const QString &newQ);

private:
    QString blank;
    QString nucid;
    QString e;
    QString de;
    QString ib;
    QString dib;
    QString logft;
    QString dft;
    QString c;
    QString un;
    QString q;
};

#endif // BETARECORD_H
