#include "ensdf.h"

ENSDF::ENSDF()
{

}

void ENSDF::setIdentification(const RecordENSDF &line)
{
    id.setNucid(line.mid(1,5));
    id.setDsid(line.mid(10,39));
    id.setDsref(line.mid(40,65));
    id.setPub(line.mid(66,74));
    id.setDate(line.mid(75,80));
}

void ENSDF::setParent(const RecordENSDF &line)
{
    parent.setNucid(line.mid(1,5));
    parent.setBlank(line.mid(6,7));
    parent.setBlank(line.at(9));
    parent.setE(line.mid(10,19));
    parent.setDe(line.mid(20,21));
    parent.setJ(line.mid(22,39));
    parent.setT(line.mid(40,49));
    parent.setDt(line.mid(50,55));
    parent.setBlank(line.mid(56,64));
    parent.setQp(line.mid(65,74));
    parent.setDqp(line.mid(75,76));
    parent.setIon(line.mid(77,80));
}

void ENSDF::setNormalization(const RecordENSDF &line)
{
    normalization.setNucid(line.mid(1,5));
    normalization.setBlank(line.mid(6,7));
    normalization.setBlank(line.at(9));
    normalization.setNr(line.mid(10,19));
    normalization.setDnr(line.mid(20,21));
    normalization.setNt(line.mid(22,29));
    normalization.setDnt(line.mid(30,31));
    normalization.setBr(line.mid(32,39));
    normalization.setDbr(line.mid(40,41));
    normalization.setNb(line.mid(42,49));
    normalization.setDnb(line.mid(50,55));
    normalization.setNp(line.mid(56,62));
    normalization.setDnp(line.mid(63,64));
    normalization.setBlank(line.mid(65,80));
}

void ENSDF::setProductionNormalization(const RecordENSDF &line)
{
    productionNormalization.setNucid(line.mid(1,5));
    productionNormalization.setBlank(line.at(6));
    productionNormalization.setBlank(line.at(9));
    productionNormalization.setNrbr(line.mid(10,19));
    productionNormalization.setUncnrbr(line.mid(20,21));
    productionNormalization.setNtbr(line.mid(22,29));
    productionNormalization.setUncntbr(line.mid(30,31));
    productionNormalization.setNbbr(line.mid(42,49));
    productionNormalization.setUncnbbr(line.mid(50,55));
    productionNormalization.setNp(line.mid(56,62));
    productionNormalization.setUncnp(line.mid(63,64));
    productionNormalization.setCom(line.at(77));
    productionNormalization.setOpt(line.at(78));
}

void ENSDF::setLevel(const RecordENSDF &line)
{
    level << LevelRecord();
    level.last().setNucid(line.mid(1,5));
    level.last().setBlank(line.mid(6,7));
    level.last().setBlank(line.at(9));
    level.last().setE(line.mid(10,19));
    level.last().setDe(line.mid(20,21));
    level.last().setJ(line.mid(22,39));
    level.last().setT(line.mid(40,49));
    level.last().setDt(line.mid(50,55));
    level.last().setL(line.mid(56,64));
    level.last().setS(line.mid(65,74));
    level.last().setDs(line.mid(75,76));
    level.last().setC(line.at(77));
    level.last().setMs(line.mid(78,79));
    level.last().setQ(line.at(80));

}

void ENSDF::setBeta(const RecordENSDF &line)
{
    BetaRecord b;
    b.setBlank(line.mid(6,7));
    b.setBlank(line.at(9));
    b.setE(line.mid(10,19));
    b.setDe(line.mid(20,21));
    b.setIb(line.mid(22,29));
    b.setDib(line.mid(30,31));
    b.setLogft(line.mid(42,49));
    b.setDft(line.mid(50,55));
    b.setBlank(line.mid(56,76));
    b.setC(line.at(77));
    b.setUn(line.mid(78,79));
    b.setQ(line.at(80));

    beta.insert(level.count()-1,b);
}

void ENSDF::setEC(const RecordENSDF &line)
{
    ECRecord e;
    e.setBlank(line.mid(6,7));
    e.setBlank(line.at(9));
    e.setE(line.mid(10,19));
    e.setDe(line.mid(20,21));
    e.setIb(line.mid(22,29));
    e.setDib(line.mid(30,31));
    e.setIe(line.mid(32,39));
    e.setDie(line.mid(40,41));
    e.setLogft(line.mid(42,49));
    e.setDft(line.mid(50,55));
    e.setTi(line.mid(65,74));
    e.setDti(line.mid(75,76));
    e.setC(line.at(77));
    e.setUn(line.mid(78,79));
    e.setQ(line.at(80));

    ec.insert(level.count() - 1, e);
}

void ENSDF::setAlpha(const RecordENSDF &line)
{
    AlphaRecord a;
    a.setBlank(line.mid(6,7));
    a.setBlank(line.at(9));
    a.setE(line.mid(10,19));
    a.setDe(line.mid(20,21));
    a.setIa(line.mid(22,29));
    a.setDia(line.mid(30,31));
    a.setHf(line.mid(32,39));
    a.setDhf(line.mid(40,41));
    a.setBlank(line.mid(42,76));
    a.setC(line.at(77));
    a.setBlank(line.mid(78,79));
    a.setQ(line.at(80));

    alpha.insert(level.count() - 1, a);
}

void ENSDF::setGamma(const RecordENSDF &line)
{
    GammaRecord g;
    g.setBlank(line.mid(6,7));
    g.setBlank(line.at(9));
    g.setE(line.mid(10,19));
    g.setDe(line.mid(20,21));
    g.setRi(line.mid(22,29));
    g.setDri(line.mid(30,31));
    g.setM(line.mid(32,41));
    g.setMr(line.mid(42,49));
    g.setDmr(line.mid(50,55));
    g.setCc(line.mid(56,62));
    g.setDcc(line.mid(63,64));
    g.setTi(line.mid(65,74));
    g.setDti(line.mid(75,76));
    g.setC(line.at(77));
    g.setCoin(line.at(78));
    g.setBlank(line.at(79));
    g.setQ(line.at(80));

    if(gamma.keys().contains(level.count()-1)) {
        gamma[level.count()-1] << g;
    }else {
        gamma.insert(level.count()-1, QVector<GammaRecord>() << g);
    }
}
