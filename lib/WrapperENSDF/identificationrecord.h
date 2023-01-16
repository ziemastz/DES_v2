#ifndef IDENTIFICATIONRECORD_H
#define IDENTIFICATIONRECORD_H

#include <QString>

class IdentificationRecord
{
public:
    IdentificationRecord();
    QString getNucid() const;
    void setNucid(const QString &newNucid);

    QString getDsid() const;
    void setDsid(const QString &newDsid);

    QString getDsref() const;
    void setDsref(const QString &newDsref);

    QString getPub() const;
    void setPub(const QString &newPub);

    QString getDate() const;
    void setDate(const QString &newDate);

private:
    QString nucid;
    QString dsid;
    QString dsref;
    QString pub;
    QString date;

};

#endif // IDENTIFICATIONRECORD_H
