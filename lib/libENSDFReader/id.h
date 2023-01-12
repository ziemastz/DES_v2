#ifndef ID_H
#define ID_H

#include <QObject>

class ID
{
public:
    ID();
    bool load(const QString &record);
    QString A;
    QString element;

private:
    void setNuclide(const QString &nucid);
    QString nucid;
    QString blank;
    QString dsid;
    QString dsref;
    QString pub;
    QString date;
};

#endif // ID_H
