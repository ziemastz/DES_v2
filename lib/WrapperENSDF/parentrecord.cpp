#include "parentrecord.h"

ParentRecord::ParentRecord()
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

QString ParentRecord::getBlank() const
{
    return blank;
}

void ParentRecord::setBlank(const QString &newBlank)
{
    blank += newBlank;
}

QString ParentRecord::getNucid() const
{
    return getX().remove(' ')+"-"+getA().remove(' ');
}

void ParentRecord::setNucid(const QString &newNucid)
{
    nucid = newNucid;
}

QString ParentRecord::getA() const
{
    return nucid.mid(0,3);
}

QString ParentRecord::getX() const
{
    return QString(nucid.at(3).toUpper())+QString(nucid.at(4).toLower());
}

int ParentRecord::getZ() const
{
    return symbols.indexOf(getX())+1;
}

QString ParentRecord::getE() const
{
    return e;
}

void ParentRecord::setE(const QString &newE)
{
    e = newE;
}

QString ParentRecord::getDe() const
{
    return de;
}

void ParentRecord::setDe(const QString &newDe)
{
    de = newDe;
}

QString ParentRecord::getJ() const
{
    return j;
}

void ParentRecord::setJ(const QString &newJ)
{
    j = newJ;
}

QString ParentRecord::getT() const
{
    return t;
}

void ParentRecord::setT(const QString &newT)
{
    t = newT;
}

QString ParentRecord::getDt() const
{
    return dt;
}

void ParentRecord::setDt(const QString &newDt)
{
    dt = newDt;
}

QString ParentRecord::getQp() const
{
    return qp;
}

void ParentRecord::setQp(const QString &newQp)
{
    qp = newQp;
}

QString ParentRecord::getDqp() const
{
    return dqp;
}

void ParentRecord::setDqp(const QString &newDqp)
{
    dqp = newDqp;
}

QString ParentRecord::getIon() const
{
    return ion;
}

void ParentRecord::setIon(const QString &newIon)
{
    ion = newIon;
}
