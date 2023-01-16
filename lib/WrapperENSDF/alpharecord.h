#ifndef ALPHARECORD_H
#define ALPHARECORD_H
#include <QString>

class AlphaRecord
{
public:
    AlphaRecord();
    QString getBlank() const;
    void setBlank(const QString &newBlank);

    QString getNucid() const;
    void setNucid(const QString &newNucid);

    QString getE() const;
    void setE(const QString &newE);

    QString getDe() const;
    void setDe(const QString &newDe);

    QString getIa() const;
    void setIa(const QString &newIa);

    QString getDia() const;
    void setDia(const QString &newDia);

    QString getHf() const;
    void setHf(const QString &newHf);

    QString getDhf() const;
    void setDhf(const QString &newDhf);

    QString getC() const;
    void setC(const QString &newC);

    QString getQ() const;
    void setQ(const QString &newQ);

private:
    QString blank;
    QString nucid;
    QString e;
    QString de;
    QString ia;
    QString dia;
    QString hf;
    QString dhf;
    QString c;
    QString q;
};

#endif // ALPHARECORD_H
