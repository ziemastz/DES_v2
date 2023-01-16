#include "alpharecord.h"

AlphaRecord::AlphaRecord()
{

}

QString AlphaRecord::getBlank() const
{
    return blank;
}

void AlphaRecord::setBlank(const QString &newBlank)
{
    blank += newBlank;
}

QString AlphaRecord::getNucid() const
{
    return nucid;
}

void AlphaRecord::setNucid(const QString &newNucid)
{
    nucid = newNucid;
}

QString AlphaRecord::getE() const
{
    return e;
}

void AlphaRecord::setE(const QString &newE)
{
    e = newE;
}

QString AlphaRecord::getDe() const
{
    return de;
}

void AlphaRecord::setDe(const QString &newDe)
{
    de = newDe;
}

QString AlphaRecord::getIa() const
{
    return ia;
}

void AlphaRecord::setIa(const QString &newIa)
{
    ia = newIa;
}

QString AlphaRecord::getDia() const
{
    return dia;
}

void AlphaRecord::setDia(const QString &newDia)
{
    dia = newDia;
}

QString AlphaRecord::getHf() const
{
    return hf;
}

void AlphaRecord::setHf(const QString &newHf)
{
    hf = newHf;
}

QString AlphaRecord::getDhf() const
{
    return dhf;
}

void AlphaRecord::setDhf(const QString &newDhf)
{
    dhf = newDhf;
}

QString AlphaRecord::getC() const
{
    return c;
}

void AlphaRecord::setC(const QString &newC)
{
    c = newC;
}

QString AlphaRecord::getQ() const
{
    return q;
}

void AlphaRecord::setQ(const QString &newQ)
{
    q = newQ;
}
