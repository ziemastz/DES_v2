#include "normalizationrecord.h"

NormalizationRecord::NormalizationRecord()
{

}

QString NormalizationRecord::getBlank() const
{
    return blank;
}

void NormalizationRecord::setBlank(const QString &newBlank)
{
    blank += newBlank;
}

QString NormalizationRecord::getNucid() const
{
    return nucid;
}

void NormalizationRecord::setNucid(const QString &newNucid)
{
    nucid = newNucid;
}

QString NormalizationRecord::getNr() const
{
    return nr;
}

void NormalizationRecord::setNr(const QString &newNr)
{
    nr = newNr;
}

QString NormalizationRecord::getDnr() const
{
    return dnr;
}

void NormalizationRecord::setDnr(const QString &newDnr)
{
    dnr = newDnr;
}

QString NormalizationRecord::getNt() const
{
    return nt;
}

void NormalizationRecord::setNt(const QString &newNt)
{
    nt = newNt;
}

QString NormalizationRecord::getDnt() const
{
    return dnt;
}

void NormalizationRecord::setDnt(const QString &newDnt)
{
    dnt = newDnt;
}

QString NormalizationRecord::getBr() const
{
    return br;
}

void NormalizationRecord::setBr(const QString &newBr)
{
    br = newBr;
}

QString NormalizationRecord::getDbr() const
{
    return dbr;
}

void NormalizationRecord::setDbr(const QString &newDbr)
{
    dbr = newDbr;
}

QString NormalizationRecord::getNb() const
{
    return nb;
}

void NormalizationRecord::setNb(const QString &newNb)
{
    nb = newNb;
}

QString NormalizationRecord::getDnb() const
{
    return dnb;
}

void NormalizationRecord::setDnb(const QString &newDnb)
{
    dnb = newDnb;
}

QString NormalizationRecord::getNp() const
{
    return np;
}

void NormalizationRecord::setNp(const QString &newNp)
{
    np = newNp;
}

QString NormalizationRecord::getDnp() const
{
    return dnp;
}

void NormalizationRecord::setDnp(const QString &newDnp)
{
    dnp = newDnp;
}
