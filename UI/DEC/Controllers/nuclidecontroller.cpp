#include "nuclidecontroller.h"

NuclideController::NuclideController() : BaseController()
{

}

NuclideModel NuclideController::getNuclide(const QString &symbol)
{
    NuclideModel ret;
    statement = QString("SELECT n.id, n.a, n.z, n.symbol, n.halfLifeValue, n.halfLifeUncer, u.unit, n.spinParity "
                        "FROM nuclide n "
                        "INNER JOIN unit_halflife u ON n.halfLifeUnit = u.id "
                        "WHERE symbol = '%1'").arg(symbol);
    QVector<QVariantList> result = db.read(statement);
    if(result.size() == 1) {
        ret.id = result.first().at(0).toInt();
        ret.a = result.first().at(0).toInt();
        ret.z = result.first().at(0).toInt();
        ret.symbol = result.first().at(0).toString();
        ret.halfLifeValue = result.first().at(0).toDouble();
        ret.halfLifeUncery = result.first().at(0).toDouble();
        ret.halfLifeUnit = result.first().at(0).toString();
        ret.spinParity = result.first().at(0).toString();
    }
    return ret;
}

QStringList NuclideController::getNuclides()
{
    QStringList ret;
    statement = QString("SELECT symbol FROM nuclide ORDER BY a");
    QVector<QVariantList> result = db.read(statement);
    for(int i=0; i<result.size(); i++) {
        ret << result.at(i).first().toString();
    }
    return ret;
}

QString NuclideController::getStandardFormatHalfLifeUnit(const QString &unit)
{
    QString ret;
    statement = QString("SELECT unit FROM unit_halflife WHERE forms LIKE '% "+unit+" %'");
    QVector<QVariantList> result = db.read(statement);
    if(result.size() == 1) {
        ret = result.first().first().toString();
    }
    return ret;
}

QStringList NuclideController::getStandardFormatHalfLifeUnits()
{
    QStringList ret;
    statement = QString("SELECT unit FROM unit_halflife");
    QVector<QVariantList> result = db.read(statement);
    for(int i=0; i<result.size(); i++) {
        ret << result.at(i).first().toString();
    }
    return ret;
}
