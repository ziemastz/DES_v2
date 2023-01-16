#include "gammarecord.h"

GammaRecord::GammaRecord()
{

}

QString GammaRecord::getBlank() const
{
    return blank;
}

void GammaRecord::setBlank(const QString &newBlank)
{
    blank += newBlank;
}

QString GammaRecord::getNucid() const
{
    return nucid;
}

void GammaRecord::setNucid(const QString &newNucid)
{
    nucid = newNucid;
}

QString GammaRecord::getE() const
{
    return e;
}

void GammaRecord::setE(const QString &newE)
{
    e = newE;
}

QString GammaRecord::getDe() const
{
    return de;
}

void GammaRecord::setDe(const QString &newDe)
{
    de = newDe;
}

QString GammaRecord::getRi() const
{
    return ri;
}

void GammaRecord::setRi(const QString &newRi)
{
    ri = newRi;
}

QString GammaRecord::getDri() const
{
    return dri;
}

void GammaRecord::setDri(const QString &newDri)
{
    dri = newDri;
}

QString GammaRecord::getM() const
{
    return m;
}

void GammaRecord::setM(const QString &newM)
{
    m = newM;
}

QString GammaRecord::getMr() const
{
    return mr;
}

void GammaRecord::setMr(const QString &newMr)
{
    mr = newMr;
}

QString GammaRecord::getDmr() const
{
    return dmr;
}

void GammaRecord::setDmr(const QString &newDmr)
{
    dmr = newDmr;
}

QString GammaRecord::getCc() const
{
    return cc;
}

void GammaRecord::setCc(const QString &newCc)
{
    cc = newCc;
}

QString GammaRecord::getDcc() const
{
    return dcc;
}

void GammaRecord::setDcc(const QString &newDcc)
{
    dcc = newDcc;
}

QString GammaRecord::getTi() const
{
    return ti;
}

void GammaRecord::setTi(const QString &newTi)
{
    ti = newTi;
}

QString GammaRecord::getDti() const
{
    return dti;
}

void GammaRecord::setDti(const QString &newDti)
{
    dti = newDti;
}

QString GammaRecord::getC() const
{
    return c;
}

void GammaRecord::setC(const QString &newC)
{
    c = newC;
}

QString GammaRecord::getCoin() const
{
    return coin;
}

void GammaRecord::setCoin(const QString &newCoin)
{
    coin = newCoin;
}

QString GammaRecord::getQ() const
{
    return q;
}

void GammaRecord::setQ(const QString &newQ)
{
    q = newQ;
}
