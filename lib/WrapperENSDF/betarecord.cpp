#include "betarecord.h"

BetaRecord::BetaRecord()
{

}

QString BetaRecord::getBlank() const
{
    return blank;
}

void BetaRecord::setBlank(const QString &newBlank)
{
    blank += newBlank;
}

QString BetaRecord::getNucid() const
{
    return nucid;
}

void BetaRecord::setNucid(const QString &newNucid)
{
    nucid = newNucid;
}

QString BetaRecord::getE() const
{
    return e;
}

void BetaRecord::setE(const QString &newE)
{
    e = newE;
}

QString BetaRecord::getDe() const
{
    return de;
}

void BetaRecord::setDe(const QString &newDe)
{
    de = newDe;
}

QString BetaRecord::getIb() const
{
    return ib;
}

void BetaRecord::setIb(const QString &newIb)
{
    ib = newIb;
}

QString BetaRecord::getDib() const
{
    return dib;
}

void BetaRecord::setDib(const QString &newDib)
{
    dib = newDib;
}

QString BetaRecord::getLogft() const
{
    return logft;
}

void BetaRecord::setLogft(const QString &newLogft)
{
    logft = newLogft;
}

QString BetaRecord::getDft() const
{
    return dft;
}

void BetaRecord::setDft(const QString &newDft)
{
    dft= newDft;
}

QString BetaRecord::getC() const
{
    return c;
}

void BetaRecord::setC(const QString &newC)
{
    c = newC;
}

QString BetaRecord::getUn() const
{
    return un;
}

void BetaRecord::setUn(const QString &newUn)
{
    un = newUn;
}

QString BetaRecord::getQ() const
{
    return q;
}

void BetaRecord::setQ(const QString &newQ)
{
    q = newQ;
}
