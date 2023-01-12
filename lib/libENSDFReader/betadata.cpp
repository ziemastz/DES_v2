#include "betadata.h"

BetaData::BetaData()
{
    level = -1;
}

bool BetaData::load(const QString &record)
{
    if(record.size() != 80)
        return false;

    nucid = record.mid(0,4);
    multiple = record.mid(5,5);
    blank = record.mid(6,6);
    blank += record.mid(8,8);
    if(multiple == ' ') {
        endpointEnergy       = record.midRef(9,18).toDouble(); // in keV
        uncerEndpointEnergy  = record.midRef(19,20).toDouble();
        intensity            = record.midRef(21,28).toDouble();
        uncerIntensity       = record.midRef(29,30).toDouble();
        blank               += record.mid(31,40);
        logFT                = record.midRef(41,48).toDouble();
        uncerLogFT           = record.midRef(49,54).toDouble();
        blank               += record.mid(55,75);
        commentFlag          = record.mid(76,76);
        forbiddenness        = record.mid(77,78);
        Q                    = record.mid(79,79);
    }else{
        // continue record
    }
    return blank.count(' ') == blank.length();
}
