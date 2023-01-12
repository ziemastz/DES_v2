#include "libensdfreader.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

LibENSDFReader::LibENSDFReader()
{
}

void LibENSDFReader::load(const QString &fileName)
{
    if(!QFile::exists(fileName)) {
        qWarning() << "Misiing file! Please check file name: " << fileName;
        return;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Error opening a file! Details: " << file.errorString();
        return;
    }
    bool isIDrecord = false;
    RecordType currentRecord;
    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();

        currentRecord = specifyRecord(line);

        if(currentRecord == RecordType::Identification) {
            isIDrecord = true;
            addNuclide();
        }
        if(isIDrecord) {
            switch(currentRecord) {
            case LibENSDFReader::Empty:
                break;
            case LibENSDFReader::Identification:
            {
                addIdentification(line);
                break;
            }
            case LibENSDFReader::History:
                break;
            case LibENSDFReader::QValue:
                break;
            case LibENSDFReader::CrossReference:
                break;
            case LibENSDFReader::Comment:
                break;
            case LibENSDFReader::Parent:
                addParent(line);
                break;
            case LibENSDFReader::Normalization:
                addNormalization(line);
                break;
            case LibENSDFReader::ProductionNormalization:
                break;
            case LibENSDFReader::Level:
                addLevel(line);
                break;
            case LibENSDFReader::Beta:
                addBeta(line);
                break;
            case LibENSDFReader::EC:
                break;
            case LibENSDFReader::Alpha:
                break;
            case LibENSDFReader::DelayedParticle:
                break;
            case LibENSDFReader::Gamma:
                break;
            case LibENSDFReader::Reference:
                break;
            case LibENSDFReader::End:
                isIDrecord = false;
                break;

            }
        }
    }
}

LibENSDFReader::RecordType LibENSDFReader::specifyRecord(const QString &record)
{
    if(record.size() != 80)
        return RecordType::Empty;

    if(record.count(' ') == record.length())
        return RecordType::End;

    QStringRef strRef = record.midRef(5,9-5);
    if(strRef.count(' ') == strRef.length())
        return RecordType::Identification;

    QChar f8 = record.at(7).toUpper();

    switch(f8.unicode()) {
    case 'X':
        return RecordType::CrossReference;
    case 'H':
        return RecordType::History;
    case 'Q':
        return RecordType::QValue;
    case ' ':
    {    if(record.at(6).unicode() == 'C')
            return RecordType::Comment;
        else
            return RecordType::Empty;
    }
    case 'P':
        return RecordType::Parent;
    case 'N':
    {
        if(record.at(6).unicode() == 'P')
            return RecordType::ProductionNormalization;
        else
            return RecordType::Normalization;
    }
    case 'L':
        return RecordType::Level;
    case 'B':
        return RecordType::Beta;
    case 'E':
        return RecordType::EC;
    case 'A':
        return RecordType::Alpha;
    case 'D':
        return RecordType::DelayedParticle;
    case 'G':
        return RecordType::Gamma;
    case 'R':
        return RecordType::Reference;
    default:
        return RecordType::Empty;
    }
}

void LibENSDFReader::addNuclide()
{
    _data << ENSDFData();
    currentNuclide = _data.count()-1;
}

void LibENSDFReader::addIdentification(const QString &record)
{
    ID id;
    if(id.load(record))
        _data[currentNuclide].id = id;
    else
        qWarning() << "Error loading identification record!";

}

void LibENSDFReader::addParent(const QString &record)
{
    ParentData parent;
    if(parent.load(record))
        _data[currentNuclide].parent = parent;
    else
        qWarning() << "Error loading parent record!";
}

void LibENSDFReader::addNormalization(const QString &record)
{
    NormalizationData normData;
    if(normData.load(record))
        _data[currentNuclide].normalization = normData;
    else
        qWarning() << "Error loading normalization record!";
}

void LibENSDFReader::addLevel(const QString &record)
{
    LevelData level;
    if(level.load(record))
        _data[currentNuclide].level << level;
    else
        qWarning() << "Error loading level record!" << _data.at(currentNuclide).level.count();
}

void LibENSDFReader::addBeta(const QString &record)
{
    BetaData beta;
    if(beta.load(record)){
        beta.level = _data.at(currentNuclide).level.count()-1;
        _data[currentNuclide].beta << beta;
    }else
        qWarning() << "Error loading level record!" << _data.at(currentNuclide).level.count();
}
