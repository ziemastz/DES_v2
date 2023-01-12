#include "parentdata.h"

ParentData::ParentData()
{

}

bool ParentData::load(const QString &record)
{
    if(record.size() != 80)
        return false;

    nucid = record.mid(0,4);
    blank = record.mid(5,6);
    multiple = record.mid(8,8);
    if(multiple == ' ') {
        energy = record.midRef(9,18).toDouble(); // in keV; (0.0 for g.s.)
        uncerEnergy     = record.midRef(19,20).toDouble();
        spinParity      = record.mid(21,38);
        halfLife        = record.mid(39,48);
        uncerHalfLife   = record.midRef(49,54).toDouble();
        blank          += record.mid(55,63);
        QValue          = record.midRef(64,73).toDouble();   // in keV (total energy avaiable for g.s->g.s. transition)
        uncerQValue     = record.midRef(74,75).toDouble();
        ionizationState = record.mid(76,79);
    }else {
        //multiple record

    }

    return blank.count(' ') == blank.length();
}
