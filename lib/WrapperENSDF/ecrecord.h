#ifndef ECRECORD_H
#define ECRECORD_H

#include <QString>

class ECRecord
{
public:
    ECRecord();
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

    QString getIe() const;
    void setIe(const QString &newIe);

    QString getDie() const;
    void setDie(const QString &newDie);

    QString getLogft() const;
    void setLogft(const QString &newLogft);

    QString getDft() const;
    void setDft(const QString &newDft);

    QString getTi() const;
    void setTi(const QString &newTi);

    QString getDti() const;
    void setDti(const QString &newDti);

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
    QString ie;
    QString die;
    QString logft;
    QString dft;
    QString ti;
    QString dti;
    QString c;
    QString un;
    QString q;

};

#endif // ECRECORD_H
