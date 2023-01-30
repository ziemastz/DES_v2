#include "atomicdatacontroller.h"

AtomicDataController::AtomicDataController() : BaseController()
{

}

AtomicDataModel AtomicDataController::getAtomicData(const QString &nuclide)
{
    AtomicDataModel ret;
    //coster-kronig
    QVector<QVariantList> result = db->read(QString("SELECT f12, f13, f23 FROM coster_kronig_yield WHERE idNuclide = '%1'").arg(nuclide));
    if(result.count() == 1) {
        ret.f12 = result.first().at(0).toDouble();
        ret.f13 = result.first().at(1).toDouble();
        ret.f23 = result.first().at(2).toDouble();
    }

    //fluorescence yields
    result = db->read(QString("SELECT s.symbol, f.yield FROM fluorescence_yield f INNER JOIN subshell s on f.idSubshell = s.id WHERE f.idNuclide ='%1'").arg(nuclide));
    for(int i=0; i<result.size(); i++) {
        QString key = result.at(i).at(0).toString();
        double value = result.at(i).at(1).toDouble();
        ret.fluorescenceYields.insert(key,value);
    }
    //radius of atoms
    result = db->read((QString("SELECT value FROM radius_nuclide WHERE id = '%1'").arg(nuclide)));
    if(result.size() == 1) {
        ret.radius = result.first().first().toDouble();
    }
    return ret;
}
