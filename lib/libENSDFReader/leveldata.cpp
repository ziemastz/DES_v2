#include "leveldata.h"

LevelData::LevelData()
{

}

bool LevelData::load(const QString &record)
{
    if(record.size() != 80)
        return false;

    nucid = record.mid(0,4);
    multiple = record.mid(5,5);
    blank = record.mid(6,6);
    blank += record.mid(8,8);

    if(multiple == ' ') {
        energy                      = record.midRef(9,18).toDouble(); // in keV (Must not be blank)
        uncerEnergy                 = record.midRef(19,20).toDouble();
        spinParity                  = record.mid(21,38);
        halfLife                    = record.mid(39,48);
        uncerHalfLife               = record.mid(49,54);
        angularMomentum             = record.mid(55,63);
        spectroscopicStrenght       = record.mid(64,73);
        uncerSpectroscopicStrenght  = record.mid(74,75);
        commentFlag                 = record.mid(76,76);
        metastableState             = record.mid(77,78);
        Q                           = record.mid(79,79);
    }else{
        // continue record
    }
    return blank.count(' ') == blank.length();
}
