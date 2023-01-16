#include "wrapperensdf.h"

WrapperENSDF::WrapperENSDF(const QString &filename)
    : _filename(filename)
{
}

bool WrapperENSDF::read()
{
    if(QFile::exists(_filename)) {
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

    RecordENSDF line;
    QTextStream in(&file);
    while(!in.atEnd()) {
        line = in.readLine();

        if(!wrap(line)) {
            return false;
        }
    }
    return true;
}

bool WrapperENSDF::wrap(const RecordENSDF &line)
{
    if(line.size() != 80) {
        qWarning() << "Data format error: Incorrect line lenght."
                      "Expected is 80 and it is " << line.size();
        return false;
    }



    //Identification Record
    if(isBlank(line.mid(6,9))) {
        qDebug() << "The Identification Record";
        raw << ENSDF();
        raw.last().setIdentification(line);
        return true;
    }

    //History Record
    if(line.at(8) == ('H' | 'h')) {
        qDebug() << "The History Record";
        return true;
    }

    //The Q-value Record
    if(line.at(8) == ('Q' | 'q')) {
        qDebug() << "The Q-value Record";
        return true;
    }

    //The Cross-Reference Record
    if(line.at(8) == ('X' | 'x')) {
        qDebug() << "The Cross-Reference Record";
        return true;
    }

    //The Comment Record
    if(line.at(7) == ('C' | 'c' | 'D' | 'd' | 'T' | 't')) {
        qDebug() << "The Comment Record";
        return true;
    }

    //The Parent Record
    if(line.at(8) == ('P' | 'p') && isBlank(line.mid(6,7))) {
        qDebug() << "The Parent Record";
        raw.last().setParent(line);
        return true;
    }

    //The Normalization Record
    if(line.at(8) == ('N' | 'n') && isBlank(line.mid(6,7))) {
        qDebug() << "The Normalization Record";
        raw.last().setNormalization(line);
        return true;
    }

    //The Production Normalization Record
    if(line.at(8) == ('N' | 'n') && line.at(7) == ('P' | 'p')  && isBlank(line.at(6))) {
        qDebug() << "The Production Normalization Record";
        raw.last().setProductionNormalization(line);
        return true;
    }

    //The Level Record
    if(line.at(8) == ('L' | 'l') && isBlank(line.mid(6,7))) {
        qDebug() << "The Level Record";
        raw.last().setLevel(line);
        return true;
    }

    //The Beta Record
    if(line.at(8) == ('B' | 'b') && isBlank(line.mid(6,7))) {
        qDebug() << "The Beta Record";
        raw.last().setBeta(line);
        return true;
    }

    //The EC (or EC + beta+) Record
    if(line.at(8) == ('E' | 'e') && isBlank(line.mid(6,7))) {
        qDebug() << "The EC (or EC + beta+) Record";
        raw.last().setEC(line);
        return true;
    }

    //The Alpha Record
    if(line.at(8) == ('A' | 'a') && isBlank(line.mid(6,7))) {
        qDebug() << "The Alpha Record";
        raw.last().setAlpha(line);
        return true;
    }

    //The (Delayed-) Particle Record
    if(line.at(8) == ('D' | 'd')) {
        qDebug() << "The (Delayed-) Particle Record";
        return true;
    }

    //The Gamma Record
    if(line.at(8) == ('G' | 'g') && isBlank(line.mid(6,7))) {
        qDebug() << "The Gamma Record";
        raw.last().setGamma(line);
        return true;
    }

    //The Reference Record
    if(line.at(8) == ('R' | 'r') && isBlank(line.mid(4,7))) {
        qDebug() << "The Reference Record";
        return true;
    }

    //The End Record
    if(isBlank(line)) {
        qDebug() << "The End Record";
        return true;
    }

    return false;
}

bool WrapperENSDF::isBlank(const RecordENSDF &str)
{
    if(str.count(QRegExp("\\s")) == str.size()) {
        return true;
    } else {
        return false;
    }
}

bool WrapperENSDF::isBlank(const QString &str)
{
    if(str.count(' ') == str.size()) {
        return true;
    } else {
        return false;
    }
}

