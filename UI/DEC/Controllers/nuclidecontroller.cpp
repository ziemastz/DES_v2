#include "nuclidecontroller.h"

NuclideController::NuclideController() : BaseController()
{

}

bool NuclideController::setNuclide(const NuclideModel &nuclide)
{
    if(!db->write(QString("DELETE FROM nuclide WHERE symbol='%1'").arg(nuclide.symbol)))
        return false;

    statement = QString("INSERT INTO nuclide VALUES (%1,%2,'%3',%4,%5,(SELECT id FROM unit_halflife WHERE unit='%6'),'%7')")
            .arg(nuclide.a)
            .arg(nuclide.z)
            .arg(nuclide.symbol)
            .arg(nuclide.halfLifeValue)
            .arg(nuclide.halfLifeUncery)
            .arg(nuclide.halfLifeUnit)
            .arg(nuclide.spinParity);
    return db->write(statement);
}

NuclideModel NuclideController::getNuclide(const QString &symbol)
{
    NuclideModel ret;
    statement = QString("SELECT n.a, n.z, n.symbol, n.halfLifeValue, n.halfLifeUncer, u.unit, n.spinParity "
                        "FROM nuclide n "
                        "INNER JOIN unit_halflife u ON n.halfLifeUnit = u.id "
                        "WHERE n.symbol = '%1'")
            .arg(symbol);
    QVector<QVariantList> result = db->read(statement);
    if(result.size() == 1) {
        int i=0;
        ret.a = result.first().at(i++).toInt();
        ret.z = result.first().at(i++).toInt();
        ret.symbol = result.first().at(i++).toString();
        ret.halfLifeValue = result.first().at(i++).toDouble();
        ret.halfLifeUncery = result.first().at(i++).toDouble();
        ret.halfLifeUnit = result.first().at(i++).toString();
        ret.spinParity = result.first().at(i++).toString();
    }
    return ret;
}

QStringList NuclideController::getNuclides()
{
    QStringList ret;
    statement = QString("SELECT symbol FROM nuclide ORDER BY a");
    QVector<QVariantList> result = db->read(statement);
    for(int i=0; i<result.size(); i++) {
        ret << result.at(i).first().toString();
    }
    return ret;
}

QString NuclideController::getStandardFormatHalfLifeUnit(const QString &unit)
{
    QString ret;
    statement = QString("SELECT unit FROM unit_halflife WHERE forms LIKE '% "+unit+" %'");
    QVector<QVariantList> result = db->read(statement);
    if(result.size() == 1) {
        ret = result.first().first().toString();
    }
    return ret;
}

QStringList NuclideController::getStandardFormatHalfLifeUnits()
{
    QStringList ret;
    statement = QString("SELECT unit FROM unit_halflife");
    QVector<QVariantList> result = db->read(statement);
    for(int i=0; i<result.size(); i++) {
        ret << result.at(i).first().toString();
    }
    return ret;
}
