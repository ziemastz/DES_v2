#include "levelrecord.h"

LevelRecord::LevelRecord()
{

}

QString LevelRecord::getBlank() const
{
    return blank;
}

void LevelRecord::setBlank(const QString &newBlank)
{
    blank += newBlank;
}

QString LevelRecord::getNucid() const
{
    return nucid.mid(3,2)+"-"+nucid.mid(0,3);
}

void LevelRecord::setNucid(const QString &newNucid)
{
    nucid = newNucid;
}

QString LevelRecord::getE() const
{
    return e;
}

void LevelRecord::setE(const QString &newE)
{
    e = newE;
}

QString LevelRecord::getDe() const
{
    return de;
}

void LevelRecord::setDe(const QString &newDe)
{
    de = newDe;
}

QString LevelRecord::getJ() const
{
    return j;
}

void LevelRecord::setJ(const QString &newJ)
{
    j = newJ;
}

QString LevelRecord::getT() const
{
    return t;
}

void LevelRecord::setT(const QString &newT)
{
    t = newT;
}

QString LevelRecord::getDt() const
{
    return dt;
}

void LevelRecord::setDt(const QString &newDt)
{
    dt = newDt;
}

QString LevelRecord::getL() const
{
    return l;
}

void LevelRecord::setL(const QString &newL)
{
    l = newL;
}

QString LevelRecord::getS() const
{
    return s;
}

void LevelRecord::setS(const QString &newS)
{
    s = newS;
}

QString LevelRecord::getDs() const
{
    return ds;
}

void LevelRecord::setDs(const QString &newDs)
{
    ds = newDs;
}

QString LevelRecord::getC() const
{
    return c;
}

void LevelRecord::setC(const QString &newC)
{
    c = newC;
}

QString LevelRecord::getMs() const
{
    return ms;
}

void LevelRecord::setMs(const QString &newMs)
{
    ms = newMs;
}

QString LevelRecord::getQ() const
{
    return q;
}

void LevelRecord::setQ(const QString &newQ)
{
    q = newQ;
}
