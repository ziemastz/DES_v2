#include "normalization.h"

NormalizationData::NormalizationData()
{

}

bool NormalizationData::load(const QString &record)
{
    if(record.size() != 80)
        return false;

    nucid = record.mid(0,4);
    blank = record.mid(5,6);
    multiple = record.mid(8,8);
    if(multiple == ' ') {
        photon               = record.midRef(9,18).toDouble();    // RI in the GAMMA record
        uncerPhoton          = record.midRef(19,20).toDouble();
        transition           = record.midRef(21,28).toDouble();
        uncerTransition      = record.midRef(29,30).toDouble();
        branchingRatio       = record.midRef(31,38).toDouble();
        uncerBranchingRatio  = record.midRef(39,40).toDouble();
        branch               = record.midRef(41,48).toDouble();   // IB in the B- record; IB, IE, TI in the EC record
        uncerBranch          = record.midRef(49,54).toDouble();
        delayed              = record.midRef(55,61).toDouble(); // delayed-transition to decays of precursor
        uncerDelayed         = record.midRef(62,63).toDouble();
        blank               += record.mid(64,79);
    }else{
        //multiple record
    }
    return blank.count(' ') == blank.length();
}
