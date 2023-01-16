#include "identificationrecord.h"

IdentificationRecord::IdentificationRecord()
{

}

QString IdentificationRecord::getNucid() const
{
    return nucid;
}

void IdentificationRecord::setNucid(const QString &newNucid)
{
    nucid = newNucid;
}

QString IdentificationRecord::getDsid() const
{
    return dsid;
}

void IdentificationRecord::setDsid(const QString &newDsid)
{
    dsid = newDsid;
}

QString IdentificationRecord::getDsref() const
{
    return dsref;
}

void IdentificationRecord::setDsref(const QString &newDsref)
{
    dsref = newDsref;
}

QString IdentificationRecord::getPub() const
{
    return pub;
}

void IdentificationRecord::setPub(const QString &newPub)
{
    pub = newPub;
}

QString IdentificationRecord::getDate() const
{
    return date;
}

void IdentificationRecord::setDate(const QString &newDate)
{
    date = newDate;
}
