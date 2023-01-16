#ifndef NORMALIZATIONRECORD_H
#define NORMALIZATIONRECORD_H
#include <QString>

class NormalizationRecord
{
public:
    NormalizationRecord();
    QString getBlank() const;
    void setBlank(const QString &newBlank);

    QString getNucid() const;
    void setNucid(const QString &newNucid);

    QString getNr() const;
    void setNr(const QString &newNr);

    QString getDnr() const;
    void setDnr(const QString &newDnr);

    QString getNt() const;
    void setNt(const QString &newNt);

    QString getDnt() const;
    void setDnt(const QString &newDnt);

    QString getBr() const;
    void setBr(const QString &newBr);

    QString getDbr() const;
    void setDbr(const QString &newDbr);

    QString getNb() const;
    void setNb(const QString &newNb);

    QString getDnb() const;
    void setDnb(const QString &newDnb);

    QString getNp() const;
    void setNp(const QString &newNp);

    QString getDnp() const;
    void setDnp(const QString &newDnp);

private:
    QString blank;

    QString nucid;
    QString nr;
    QString dnr;
    QString nt;
    QString dnt;
    QString br;
    QString dbr;
    QString nb;
    QString dnb;
    QString np;
    QString dnp;
};

#endif // NORMALIZATIONRECORD_H
