#include "ecrecord.h"

ECRecord::ECRecord()
{

}

QString ECRecord::getBlank() const
{
    return blank;
}

void ECRecord::setBlank(const QString &newBlank)
{
    blank += newBlank;
}

QString ECRecord::getNucid() const
{
    return nucid;
}

void ECRecord::setNucid(const QString &newNucid)
{
    nucid = newNucid;
}

QString ECRecord::getE() const
{
    return e;
}

void ECRecord::setE(const QString &newE)
{
    e = newE;
}

QString ECRecord::getDe() const
{
    return de;
}

void ECRecord::setDe(const QString &newDe)
{
    de = newDe;
}

QString ECRecord::getIb() const
{
    return ib;
}

void ECRecord::setIb(const QString &newIb)
{
    ib = newIb;
}

QString ECRecord::getDib() const
{
    return dib;
}

void ECRecord::setDib(const QString &newDib)
{
    dib = newDib;
}

QString ECRecord::getIe() const
{
    return ie;
}

void ECRecord::setIe(const QString &newIe)
{
    ie = newIe;
}

QString ECRecord::getDie() const
{
    return die;
}

void ECRecord::setDie(const QString &newDie)
{
    die = newDie;
}

QString ECRecord::getLogft() const
{
    return logft;
}

void ECRecord::setLogft(const QString &newLogft)
{
    logft = newLogft;
}

QString ECRecord::getDft() const
{
    return dft;
}

void ECRecord::setDft(const QString &newDft)
{
    dft = newDft;
}

QString ECRecord::getTi() const
{
    return ti;
}

void ECRecord::setTi(const QString &newTi)
{
    ti = newTi;
}

QString ECRecord::getDti() const
{
    return dti;
}

void ECRecord::setDti(const QString &newDti)
{
    dti = newDti;
}

QString ECRecord::getC() const
{
    return c;
}

void ECRecord::setC(const QString &newC)
{
    c = newC;
}

QString ECRecord::getUn() const
{
    return un;
}

void ECRecord::setUn(const QString &newUn)
{
    un = newUn;
}

QString ECRecord::getQ() const
{
    return q;
}

void ECRecord::setQ(const QString &newQ)
{
    q = newQ;
}
