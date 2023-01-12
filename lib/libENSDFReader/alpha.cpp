#include "alpha.h"

Alpha::Alpha()
{

}

bool Alpha::load(const QString &record)
{
    if(record.size() != 80)
        return false;

    nucid = record.mid(0,5);
    multiple = record.mid(5,1);
    blank = record.mid(6,1);
    blank += record.mid(8,1);
    if(multiple == ' ') {
        energy               = record.midRef(9,18).toDouble(); // in keV
        uncerEnergy          = record.midRef(19,20).toDouble();
        intensity            = record.midRef(21,28).toDouble();
        uncerIntensity       = record.midRef(29,30).toDouble();
        hindranceFactor      = record.midRef(31,38).toDouble();
        uncerHindranceFactor = record.midRef(39,40).toDouble();
        blank               += record.mid(41,75);
        commentFlag          = record.mid(76,76);
        blank               += record.mid(77,78);
        Q                    = record.mid(79,79);
    }else{
        // continue record ?????
    }
    return blank.count(' ') == blank.length();
}
