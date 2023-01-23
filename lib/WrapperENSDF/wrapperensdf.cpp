#include "wrapperensdf.h"

WrapperENSDF::WrapperENSDF(const QString &filename)
    : _filename(filename)
{
}

bool WrapperENSDF::read()
{
    if(!QFile::exists(_filename)) {
        qWarning() << "File isn't exists! File provided: " << _filename;
        return false;
    }
    qDebug() << "Start reading file " << _filename << "...";

    QFile file(_filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file! Error: " << file.errorString();
        return false;
    }
    qDebug() << "File opened.";
    count_line = 1;
    RecordENSDF line;
    QTextStream in(&file);
    while(!in.atEnd()) {
        line = in.readLine();

        if(!wrap(line)) {
            return false;
        }
        count_line++;
    }
    return true;
}

QString WrapperENSDF::getParent() const
{
    if(raw.isEmpty())
        return QString();
    return raw.first().getParent().getNucid();
}

QString WrapperENSDF::getParent(const int &noDaughter) const
{
    if(noDaughter < raw.count())
        return raw.at(noDaughter).getParent().getNucid();
    else
        return QString();
}

QString WrapperENSDF::getHalfLifeValueParent(const int &noDaughter) const
{
    if(noDaughter < raw.count())
        return raw.at(noDaughter).getParent().getT().split(QRegExp("\\s"),Qt::SkipEmptyParts).first();
    else
        return QString();
}

QString WrapperENSDF::getHalfLifeUncertaintyParent(const int &noDaughter) const
{
    if(noDaughter < raw.count())
        return raw.at(noDaughter).getParent().getDt();
    else
        return QString();
}

QString WrapperENSDF::getHalfLifeUnitParent(const int &noDaughter) const
{
    if(noDaughter < raw.count())
        return raw.at(noDaughter).getParent().getT().split(QRegExp("\\s"),Qt::SkipEmptyParts).last();
    else
        return QString();
}

QString WrapperENSDF::getSpinParityParent(const int &noDaughter) const
{
    if(noDaughter < raw.count())
        return raw.at(noDaughter).getParent().getJ();
    else
        return QString();
}

int WrapperENSDF::countDaughters() const
{
    return raw.count();
}

QString WrapperENSDF::getDaughter(const int &noDaughter) const
{
    return raw.at(noDaughter).getLevel().first().getNucid();
}

QString WrapperENSDF::getHalfLifeValueDaughter(const int &noDaughter) const
{
    if(noDaughter < raw.count())
        return raw.at(noDaughter).getLevel().first().getT().split(QRegExp("\\s"),Qt::SkipEmptyParts).first();
    else
        return QString();
}

QString WrapperENSDF::getHalfLifeUncertaintyDaughter(const int &noDaughter) const
{
    if(noDaughter < raw.count())
        return raw.at(noDaughter).getLevel().first().getDt();
    else
        return QString();
}

QString WrapperENSDF::getHalfLifeUnitDaughter(const int &noDaughter) const
{
    if(noDaughter < raw.count())
        return raw.at(noDaughter).getLevel().first().getT().split(QRegExp("\\s"),Qt::SkipEmptyParts).last();
    else
        return QString();
}

int WrapperENSDF::countLevels(const int &noDaughter) const
{
    return raw.at(noDaughter).getLevel().count();
}

QString WrapperENSDF::getLevelEnergy(const int &noDaughter, const int &noLevel) const
{
    return raw.at(noDaughter).getLevel().at(noLevel).getE();
}

QString WrapperENSDF::getHalfLifeValueLevel(const int &noDaughter, const int &noLevel) const
{
    if(noDaughter < raw.count()) {
        if(!isBlank(raw.at(noDaughter).getLevel().at(noLevel).getT()))
            return raw.at(noDaughter).getLevel().at(noLevel).getT().split(QRegExp("\\s"),Qt::SkipEmptyParts).first();
        else
            return QString();
    }else
        return QString();
}

QString WrapperENSDF::getHalfLifeUncertaintyLevel(const int &noDaughter, const int &noLevel) const
{
    if(noDaughter < raw.count())
        return raw.at(noDaughter).getLevel().at(noLevel).getDt();
    else
        return QString();
}

QString WrapperENSDF::getHalfLifeUnitLevel(const int &noDaughter, const int &noLevel) const
{
    if(noDaughter < raw.count())
        if(!isBlank(raw.at(noDaughter).getLevel().at(noLevel).getT()))
            return raw.at(noDaughter).getLevel().at(noLevel).getT().split(QRegExp("\\s"),Qt::SkipEmptyParts).last();
        else
            return QString();
    else
        return QString();
}

bool WrapperENSDF::findBeta(const int &noDaughter, const int &noLevel) const
{
    return raw.at(noDaughter).getBeta().contains(noLevel);
}

QString WrapperENSDF::getIntensityBeta(const int &noDaughter, const int &noLevel) const
{
    return raw.at(noDaughter).getBeta().value(noLevel).getIb();
}

bool WrapperENSDF::findAlpha(const int &noDaughter, const int &noLevel) const
{
    return raw.at(noDaughter).getAlpha().contains(noLevel);
}

QString WrapperENSDF::getIntensityAlpha(const int &noDaughter, const int &noLevel) const
{
    return raw.at(noDaughter).getAlpha().value(noLevel).getIa();
}

bool WrapperENSDF::findEC(const int &noDaughter, const int &noLevel) const
{
    return raw.at(noDaughter).getEC().contains(noLevel);
}

QString WrapperENSDF::getIntensityEC(const int &noDaughter, const int &noLevel) const
{
    return raw.at(noDaughter).getEC().value(noLevel).getIe();
}

int WrapperENSDF::countGammas(const int &noDaughter, const int &noLevel) const
{
    return raw.at(noDaughter).getGamma().value(noLevel).count();
}

QString WrapperENSDF::getGammaEnergy(const int &noDaughter, const int &noLevel, const int &noGamma) const
{
    return raw.at(noDaughter).getGamma().value(noLevel).at(noGamma).getE();
}

QString WrapperENSDF::getGammaIntensity(const int &noDaughter, const int &noLevel, const int &noGamma) const
{
    return raw.at(noDaughter).getGamma().value(noLevel).at(noGamma).getRi();
}

QString WrapperENSDF::getGammaMultipolarity(const int &noDaughter, const int &noLevel, const int &noGamma) const
{
    return raw.at(noDaughter).getGamma().value(noLevel).at(noGamma).getM();
}

QString WrapperENSDF::getGammaTotalElectronConvertion(const int &noDaughter, const int &noLevel, const int &noGamma) const
{
    return raw.at(noDaughter).getGamma().value(noLevel).at(noGamma).getCc();
}

QString WrapperENSDF::getFinalLevelEnergy(const int &noDaughter, const int &noLevel, const int &noGamma) const
{
    double intial = getLevelEnergy(noDaughter,noLevel).toDouble();
    double gammaEnergy = getGammaEnergy(noDaughter,noLevel,noGamma).toDouble();
    double dev = intial - gammaEnergy;
    int closestLevel = 0;
    double lowestEnergy = dev;
    for(int i = noLevel-1; i >= 0; i--) {
        double nextLevel = getLevelEnergy(noDaughter,i).toDouble();
        if(abs(nextLevel - dev) <= lowestEnergy){
            closestLevel = i;
            lowestEnergy = abs(nextLevel - dev);
        }
    }
    return getLevelEnergy(noDaughter,closestLevel);
}

bool WrapperENSDF::wrap(const RecordENSDF &line)
{
    if(line.size() != 80) {
        qWarning() << count_line << "\t" << "Data format error: Incorrect line lenght."
                      "Expected is 80 and it is " << line.size();
        return false;
    }

    //The End Record
    if(isBlank(line)) {
        qDebug() << count_line << "\t"  << "The End Record";
        return true;
    }

    //Identification Record
    if(isBlank(line.mid(6,9))) {
        qDebug() << count_line << "\t"  << "The Identifi"
                                           "cation Record";
        raw << ENSDF();
        raw.last().setIdentification(line);
        return true;
    }

    //History Record
    if(line.at(8).toUpper() == 'H') {
        if(isBlank(line.mid(6,7))) {
            qDebug() << count_line << "\t"  << "The History Record";
        }else {
            qDebug() << count_line << "\t"  << "The History Record continuation record";
        }
        return true;
    }

    //The Q-value Record
    if(line.at(8).toUpper() == 'Q' && isBlank(line.mid(6,7))) {
        qDebug() << count_line << "\t"  << "The Q-value Record";
        return true;
    }

    //The Cross-Reference Record
    if(line.at(8).toUpper() == 'X' && isBlank(line.mid(6,7))) {
        qDebug() << count_line << "\t"  << "The Cross-Reference Record";
        return true;
    }

    //The Comment/Document/Table Record
    if(line.at(7).toUpper() == 'C' ||
       line.at(7).toUpper() == 'D' ||
       line.at(7).toUpper() == 'T') {
        if(isBlank(line.at(6))) {
            qDebug() << count_line << "\t"  << "The Comment/Document/Table Record";
        }else {
            qDebug() << count_line << "\t"  << "The Comment/Document/Table Record - continuation record";
        }
        return true;
    }

    //The Parent Record
    if(line.at(8).toUpper() == 'P' && isBlank(line.mid(6,7))) {
        qDebug() << count_line << "\t"  << "The Parent Record";
        raw.last().setParent(line);
        return true;
    }

    //The Normalization Record
    if(line.at(8).toUpper() == 'N' && isBlank(line.mid(6,7))) {
        qDebug() << count_line << "\t"  << "The Normalization Record";
        raw.last().setNormalization(line);
        return true;
    }

    //The Production Normalization Record
    if(line.at(8).toUpper() == 'N' && line.at(7).toUpper() == 'P') {
        if(isBlank(line.at(6))) {
            qDebug() << count_line << "\t"  << "The Production Normalization Record";
            raw.last().setProductionNormalization(line);
        }else {
            qDebug() << count_line << "\t"  << "The Production Normalization Record - continuation record";
        }
        return true;
    }

    //The Level Record
    if(line.at(8).toUpper() == 'L') {
        if(isBlank(line.mid(6,7))) {
            qDebug() << count_line << "\t"  << "The Level Record";
            raw.last().setLevel(line);
        }else {
            qDebug() << count_line << "\t"  << "The Level Record - continuation record";
        }
        return true;
    }

    //The Beta Record
    if(line.at(8).toUpper() == 'B') {
        if(isBlank(line.mid(6,7))) {
            qDebug() << count_line << "\t"  << "The Beta Record";
            raw.last().setBeta(line);
        }else {
            qDebug() << count_line << "\t"  << "The Beta Record - continuation record";
        }
        return true;
    }

    //The EC (or EC + beta+) Record
    if(line.at(8).toUpper() == 'E') {
        if(isBlank(line.mid(6,7))) {
            qDebug() << count_line << "\t"  << "The EC (or EC + beta+) Record";
            raw.last().setEC(line);
        }else {
            qDebug() << count_line << "\t"  << "The EC (or EC + beta+) Record - continuation record";
        }
        return true;
    }

    //The Alpha Record
    if(line.at(8).toUpper() == 'A') {
        if(isBlank(line.mid(6,7))) {
            qDebug() << count_line << "\t"  << "The Alpha Record";
            raw.last().setAlpha(line);
        }else {
            qDebug() << count_line << "\t"  << "The Alpha Record - continuation record";
        }
        return true;
    }

    //The (Delayed-) Particle Record
    if(line.at(8).toUpper() == 'D') {
        if(isBlank(line.mid(6,7))) {
            qDebug() << count_line << "\t"  << "The (Delayed-) Particle Record";
        }else {
            qDebug() << count_line << "\t"  << "The (Delayed-) Particle Record - continuation record";
        }
        return true;
    }

    //The Gamma Record
    if(line.at(8).toUpper() == 'G') {
        if(isBlank(line.mid(6,7))) {
            qDebug() << count_line << "\t"  << "The Gamma Record";
            raw.last().setGamma(line);
        }else {
            qDebug() << count_line << "\t"  << "The Gamma Record - continuation record";
        }
        return true;
    }

    //The Reference Record
    if(line.at(8).toUpper() == 'R' && isBlank(line.mid(4,7))) {
        qDebug() << count_line << "\t"  << "The Reference Record";
        return true;
    }



    return false;
}

bool WrapperENSDF::isBlank(const RecordENSDF &str) const
{
    if(str.count(QRegExp("\\s")) == str.size()) {
        return true;
    } else {
        return false;
    }
}

bool WrapperENSDF::isBlank(const QString &str) const
{
    if(str.count(' ') == str.size()) {
        return true;
    } else {
        return false;
    }
}

