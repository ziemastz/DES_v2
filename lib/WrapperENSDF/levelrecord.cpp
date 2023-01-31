#include "levelrecord.h"

LevelRecord::LevelRecord()
{
    symbols     << "H " << "He" << "Li" << "Be" << "B " << "C "
                << "N " << "O " << "F " << "Ne" << "Na" << "Mg"
                << "Al" << "Si" << "P " << "S " << "Cl" << "Ar"
                << "K " << "Ca" << "Sc" << "Ti" << "V " << "Cr"
                << "Mn" << "Fe" << "Co" << "Ni" << "Cu" << "Zn"
                << "Ga" << "Ge" << "As" << "Se" << "Br" << "Kr"
                << "Rb" << "Sr" << "Y " << "Zr" << "Nb" << "Mo"
                << "Tc" << "Ru" << "Rh" << "Pd" << "Ag" << "Cd"
                << "In" << "Sn" << "Sb" << "Te" << "I " << "Xe"
                << "Cs" << "Ba" << "La" << "Ce" << "Pr" << "Nd"
                << "Pm" << "Sm" << "Eu" << "Gd" << "Tb" << "Dy"
                << "Ho" << "Er" << "Tm" << "Yb" << "Lu" << "Hf"
                << "Ta" << "W " << "Re" << "Os" << "Ir" << "Pt"
                << "Au" << "Hg" << "Tl" << "Pb" << "Bi" << "Po"
                << "At" << "Rn" << "Fr" << "Ra" << "Ac" << "Th"
                << "Pa" << "U " << "Np" << "Pu" << "Am" << "Cm"
                << "Bk" << "Cf" << "Es" << "Fm" << "Md" << "No"
                << "Lr" << "Rf";
}

QString LevelRecord::getBlank() const
{
    return blank;
}

void LevelRecord::setBlank(const QString &newBlank)
{
    blank += newBlank;
}

QString LevelRecord::getNucid() const
{
    return getX().remove(' ')+"-"+getA().remove(' ');
}

void LevelRecord::setNucid(const QString &newNucid)
{
    nucid = newNucid;
}

QString LevelRecord::getA() const
{
    return nucid.mid(0,3);
}

QString LevelRecord::getX() const
{
    return QString(nucid.at(3).toUpper())+QString(nucid.at(4).toLower());
}

int LevelRecord::getZ() const
{
    return symbols.indexOf(getX())+1;
}

QString LevelRecord::getE() const
{
    return e;
}

void LevelRecord::setE(const QString &newE)
{
    e = newE;
}

QString LevelRecord::getDe() const
{
    return de;
}

void LevelRecord::setDe(const QString &newDe)
{
    de = newDe;
}

QString LevelRecord::getJ() const
{
    return j;
}

void LevelRecord::setJ(const QString &newJ)
{
    j = newJ;
}

QString LevelRecord::getT() const
{
    return t;
}

void LevelRecord::setT(const QString &newT)
{
    t = newT;
}

QString LevelRecord::getDt() const
{
    return dt;
}

void LevelRecord::setDt(const QString &newDt)
{
    dt = newDt;
}

QString LevelRecord::getL() const
{
    return l;
}

void LevelRecord::setL(const QString &newL)
{
    l = newL;
}

QString LevelRecord::getS() const
{
    return s;
}

void LevelRecord::setS(const QString &newS)
{
    s = newS;
}

QString LevelRecord::getDs() const
{
    return ds;
}

void LevelRecord::setDs(const QString &newDs)
{
    ds = newDs;
}

QString LevelRecord::getC() const
{
    return c;
}

void LevelRecord::setC(const QString &newC)
{
    c = newC;
}

QString LevelRecord::getMs() const
{
    return ms;
}

void LevelRecord::setMs(const QString &newMs)
{
    ms = newMs;
}

QString LevelRecord::getQ() const
{
    return q;
}

void LevelRecord::setQ(const QString &newQ)
{
    q = newQ;
}
