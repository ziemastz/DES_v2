#ifndef PRODUCTIONNORMALIZATIONRECORD_H
#define PRODUCTIONNORMALIZATIONRECORD_H

#include <QString>

class ProductionNormalizationRecord
{
public:
    ProductionNormalizationRecord();
    QString getBlank() const;
    void setBlank(const QString &newBlank);

    QString getNucid() const;
    void setNucid(const QString &newNucid);

    QString getNrbr() const;
    void setNrbr(const QString &newNrbr);

    QString getUncnrbr() const;
    void setUncnrbr(const QString &newUncnrbr);

    QString getNtbr() const;
    void setNtbr(const QString &newNtbr);

    QString getUncntbr() const;
    void setUncntbr(const QString &newUncntbr);

    QString getNbbr() const;
    void setNbbr(const QString &newNbbr);

    QString getUncnbbr() const;
    void setUncnbbr(const QString &newUncnbbr);

    QString getNp() const;
    void setNp(const QString &newNp);

    QString getUncnp() const;
    void setUncnp(const QString &newUncnp);

    QString getCom() const;
    void setCom(const QString &newCom);

    QString getOpt() const;
    void setOpt(const QString &newOpt);

private:
    QString blank;

    QString nucid;
    QString nrbr;
    QString uncnrbr;
    QString ntbr;
    QString uncntbr;
    QString nbbr;
    QString uncnbbr;
    QString np;
    QString uncnp;
    QString com;
    QString opt;
};

#endif // PRODUCTIONNORMALIZATIONRECORD_H
