#include "atomicdatacontroller.h"

AtomicDataController::AtomicDataController()
{
    qDebug() << "AtomicDataController contructor";
}

AtomicDataModel AtomicDataController::getAtomicData(const QString &nuclide)
{
    AtomicDataModel ret;
    QVector<QVariantList> result = db.read(QString("select f12, f13, f23"
                                           "from coster_kronig_yield c"
                                           "inner join nuclide n on c.idNuclide = n.symbol"
                                           "where n.symbol = '%1'").arg(nuclide));
    if(result.count() == 1) {
        ret.f12 = result.first().at(0).toString();
        ret.f13 = result.first().at(1).toString();
        ret.f23 = result.first().at(2).toString();
    }
    result = db.read(QString("select s.symbol, f.yield"
                             "from fluorescence_yield f"
                             "inner join nuclide n on n.symbol = f.idNuclide"
                             "inner join subshell s on f.idSubshell = s.id"
                             "where n.symbol ='%1'").arg(nuclide));
    for(int i=0; i<result.size(); i++) {
        QString key = result.at(i).at(0).toString();
        QString value = result.at(i).at(1).toString();
        ret.fluorescenceYields.insert(key,value);
    }
    return ret;
}
