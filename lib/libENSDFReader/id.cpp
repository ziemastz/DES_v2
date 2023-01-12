#include "id.h"

ID::ID()
{

}

bool ID::load(const QString &record)
{
    if(record.size() != 80)
        return false;
    nucid = record.mid(0,5);
    blank = record.mid(5,4);
    dsid = record.mid(9,30);
    dsref = record.mid(39,26);
    pub = record.mid(65,9);
    date = record.mid(74,6);

    return blank.count(' ') == blank.length();
}

void ID::setNuclide(const QString &nucid)
{
    if(nucid.size() != 5)
        return;

   A = nucid.mid(0,3).remove(QRegExp("\\s"));
   element = nucid.mid(3,2).remove(QRegExp("\\s"));
}
