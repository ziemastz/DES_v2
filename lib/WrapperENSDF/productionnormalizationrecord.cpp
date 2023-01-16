#include "productionnormalizationrecord.h"

ProductionNormalizationRecord::ProductionNormalizationRecord()
{

}

QString ProductionNormalizationRecord::getBlank() const
{
    return blank;
}

void ProductionNormalizationRecord::setBlank(const QString &newBlank)
{
    blank += newBlank;
}

QString ProductionNormalizationRecord::getNucid() const
{
    return nucid;
}

void ProductionNormalizationRecord::setNucid(const QString &newNucid)
{
    nucid = newNucid;
}

QString ProductionNormalizationRecord::getNrbr() const
{
    return nrbr;
}

void ProductionNormalizationRecord::setNrbr(const QString &newNrbr)
{
    nrbr = newNrbr;
}

QString ProductionNormalizationRecord::getUncnrbr() const
{
    return uncnrbr;
}

void ProductionNormalizationRecord::setUncnrbr(const QString &newUncnrbr)
{
    uncnrbr = newUncnrbr;
}

QString ProductionNormalizationRecord::getNtbr() const
{
    return ntbr;
}

void ProductionNormalizationRecord::setNtbr(const QString &newNtbr)
{
    ntbr = newNtbr;
}

QString ProductionNormalizationRecord::getUncntbr() const
{
    return uncntbr;
}

void ProductionNormalizationRecord::setUncntbr(const QString &newUncntbr)
{
    uncntbr = newUncntbr;
}

QString ProductionNormalizationRecord::getNbbr() const
{
    return nbbr;
}

void ProductionNormalizationRecord::setNbbr(const QString &newNbbr)
{
    nbbr = newNbbr;
}

QString ProductionNormalizationRecord::getUncnbbr() const
{
    return uncnbbr;
}

void ProductionNormalizationRecord::setUncnbbr(const QString &newUncnbbr)
{
    uncnbbr = newUncnbbr;
}

QString ProductionNormalizationRecord::getNp() const
{
    return np;
}

void ProductionNormalizationRecord::setNp(const QString &newNp)
{
    np = newNp;
}

QString ProductionNormalizationRecord::getUncnp() const
{
    return uncnp;
}

void ProductionNormalizationRecord::setUncnp(const QString &newUncnp)
{
    uncnp = newUncnp;
}

QString ProductionNormalizationRecord::getCom() const
{
    return com;
}

void ProductionNormalizationRecord::setCom(const QString &newCom)
{
    com = newCom;
}

QString ProductionNormalizationRecord::getOpt() const
{
    return opt;
}

void ProductionNormalizationRecord::setOpt(const QString &newOpt)
{
    opt = newOpt;
}
