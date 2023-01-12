#include "gamma.h"

Gamma::Gamma()
{

}

bool Gamma::load(const QString &record)
{
    if(record.size() != 80)
        return false;

    nucid = record.mid(0,4);
    multiple = record.mid(5,5);
    blank = record.mid(6,6);
    blank += record.mid(8,8);
    if(multiple == ' ') {
        energy               = record.midRef(9,18).toDouble(); // in keV
        uncerEnergy          = record.midRef(19,20).toDouble();
        intensity            = record.midRef(21,28).toDouble();
        uncerIntensity       = record.midRef(29,30).toDouble();
        multipolarity      = record.mid(31,40);
        mixingRatio = record.midRef(41,48).toDouble();
        uncerMixingRatio = record.midRef(49,54).toDouble();
        conversionTotal = record.midRef(55,61).toDouble();
        uncerConversionTotal = record.midRef(62,63).toDouble();
        intensityTotal            = record.midRef(64,73).toDouble();
        uncerIntensityTotal       = record.midRef(74,75).toDouble();
        commentFlag          = record.mid(76,76);
        coincidence          = record.mid(77,77);
        blank               += record.mid(78,78);
        Q                    = record.mid(79,79);
    }else{
        // continue record
    }
    return blank.count(' ') == blank.length();
}
