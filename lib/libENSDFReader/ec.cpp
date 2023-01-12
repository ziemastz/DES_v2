#include "ec.h"

EC::EC()
{

}

bool EC::load(const QString &record)
{
    if(record.size() != 80)
        return false;

    nucid = record.mid(0,4);
    multiple = record.mid(5,5);
    blank = record.mid(6,6);
    blank += record.mid(8,8);
    if(multiple == ' ') {
        energy       = record.midRef(9,18).toDouble(); // in keV
        uncerEnergy  = record.midRef(19,20).toDouble();
        intensityBeta            = record.midRef(21,28).toDouble();
        uncerIntensityBeta       = record.midRef(29,30).toDouble();
        intensityEC            = record.midRef(31,38).toDouble();
        uncerIntensityEC       = record.midRef(39,40).toDouble();
        logFT                = record.midRef(41,48).toDouble();
        uncerLogFT           = record.midRef(49,54).toDouble();
        intensityTotal            = record.midRef(64,73).toDouble();
        uncerIntensityTotal       = record.midRef(74,75).toDouble();
        commentFlag          = record.mid(76,76);
        forbiddenness        = record.mid(77,78);
        Q                    = record.mid(79,79);
    }else{
        // continue record
    }
    return blank.count(' ') == blank.length();
}
