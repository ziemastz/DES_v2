#include "parentrecord.h"

ParentRecord::ParentRecord()
{

}

QString ParentRecord::getBlank() const
{
    return blank;
}

void ParentRecord::setBlank(const QString &newBlank)
{
    blank += newBlank;
}

QString ParentRecord::getNucid() const
{
    return nucid.mid(3,2)+"-"+nucid.mid(0,3);
}

void ParentRecord::setNucid(const QString &newNucid)
{
    nucid = newNucid;
}

QString ParentRecord::getE() const
{
    return e;
}

void ParentRecord::setE(const QString &newE)
{
    e = newE;
}

QString ParentRecord::getDe() const
{
    return de;
}

void ParentRecord::setDe(const QString &newDe)
{
    de = newDe;
}

QString ParentRecord::getJ() const
{
    return j;
}

void ParentRecord::setJ(const QString &newJ)
{
    j = newJ;
}

QString ParentRecord::getT() const
{
    return t;
}

void ParentRecord::setT(const QString &newT)
{
    t = newT;
}

QString ParentRecord::getDt() const
{
    return dt;
}

void ParentRecord::setDt(const QString &newDt)
{
    dt = newDt;
}

QString ParentRecord::getQp() const
{
    return qp;
}

void ParentRecord::setQp(const QString &newQp)
{
    qp = newQp;
}

QString ParentRecord::getDqp() const
{
    return dqp;
}

void ParentRecord::setDqp(const QString &newDqp)
{
    dqp = newDqp;
}

QString ParentRecord::getIon() const
{
    return ion;
}

void ParentRecord::setIon(const QString &newIon)
{
    ion = newIon;
}
