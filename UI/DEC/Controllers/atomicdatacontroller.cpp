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
    // subshells
    statement = QString("SELECT s.symbol, a.binding_energy_keV, a.electrons, s.id "
                        "FROM atomic_subshell a "
                        "LEFT JOIN subshell s ON s.id = a.idSubshell "
                        "WHERE idNuclide = '%1'")
            .arg(nuclide);
    result = db->read(statement);
    for(int i=0; i<result.size(); i++) {
        int j=0;
        QString key = result.at(i).at(j++).toString();
        AtomicSubshellModel subshell;
        subshell.binding_energy_keV = result.at(i).at(j++).toDouble();
        subshell.elektrons_max = result.at(i).at(j++).toInt();
        int idSubshell = result.at(i).at(j++).toInt();
        //auger
        statement = QString("SELECT transition, intensity "
                            "FROM atomic_auger_transition "
                            "WHERE idNuclide = '%1' AND idSubshell = %2")
                .arg(nuclide)
                .arg(idSubshell);
        QVector<QVariantList> p_res = db->read(statement);
        for(int a=0; a<p_res.size(); a++) {
            QString key = p_res.at(a).at(0).toString();
            double value = p_res.at(a).at(1).toDouble();
            subshell.auger.insert(key,value);
        }
        //x-ray
        statement = QString("SELECT transition, intensity "
                            "FROM atomic_x_ray_transition "
                            "WHERE idNuclide = '%1' AND idSubshell = %2")
                .arg(nuclide)
                .arg(idSubshell);
        p_res = db->read(statement);
        for(int a=0; a<p_res.size(); a++) {
            QString key = p_res.at(a).at(0).toString();
            double value = p_res.at(a).at(1).toDouble();
            subshell.xRay.insert(key,value);
        }
        ret.subshells.insert(key,subshell);
    }
    return ret;
}

bool AtomicDataController::updateAtomicData(const QString &nuclide, const AtomicDataModel &atomic)
{
    if(!db->write("BEGIN TRANSACTION"))
        return false;

    // step 1: delete
    if(!db->write(QString("DELETE FROM atomic_subshell WHERE idNuclide='%1'").arg(nuclide))) {
        db->write("ROLLBACK");
        return false;
    }
    // step 2 insert subshell data
    QMap<QString,AtomicSubshellModel>::const_iterator iter = atomic.subshells.begin();
    while(iter != atomic.subshells.end()) {
        QString subshell = iter.key();
        AtomicSubshellModel data = iter.value();
        statement = QString("INSERT INTO atomic_subshell "
                            "VALUES('%1', "
                            "(SELECT id FROM subshell WHERE symbol='%2'), "
                            "%3, %4)")
                .arg(nuclide)
                .arg(subshell)
                .arg(data.binding_energy_keV)
                .arg(data.elektrons_max);

        if(!db->write(statement)) {
            db->write("ROLLBACK");
            return false;
        }
        //auger transition
        QMap<QString,double>::const_iterator a_iter = data.auger.begin();
        while(a_iter != data.auger.end()) {
            QString transition = a_iter.key();
            double intensity = a_iter.value();
            statement = QString("INSERT INTO atomic_auger_transition "
                               "VALUES('%1', "
                               "(SELECT id FROM subshell WHERE symbol='%2'), "
                               "'%3', %4)")
                   .arg(nuclide)
                   .arg(subshell)
                   .arg(transition)
                   .arg(intensity);
            if(!db->write(statement)) {
                db->write("ROLLBACK");
                return false;
            }
            ++a_iter;
        }
        //x-ray transition
        QMap<QString,double>::const_iterator x_iter = data.xRay.begin();
        while(x_iter != data.xRay.end()) {
            QString transition = x_iter.key();
            double intensity = x_iter.value();
            statement = QString("INSERT INTO atomic_x_ray_transition "
                               "VALUES('%1', "
                               "(SELECT id FROM subshell WHERE symbol='%2'), "
                               "'%3', %4)")
                   .arg(nuclide)
                   .arg(subshell)
                   .arg(transition)
                   .arg(intensity);
            if(!db->write(statement)) {
                db->write("ROLLBACK");
                return false;
            }
            ++x_iter;
        }
        ++iter;
    }
    // atomic data nuclide
    statement = QString("INSERT INTO coster_kronig_yield "
                        "VALUES('%1', %2, %3, %4)")
            .arg(nuclide)
            .arg(atomic.f12)
            .arg(atomic.f13)
            .arg(atomic.f23);
    if(!db->write(statement)) {
        db->write("ROLLBACK");
        return false;
    }

    statement = QString("INSERT INTO radius_nuclide "
                        "VALUES('%1', %2)")
            .arg(nuclide)
            .arg(atomic.radius);
    if(!db->write(statement)) {
        db->write("ROLLBACK");
        return false;
    }

    QMap<QString,double>::const_iterator f_iter = atomic.fluorescenceYields.begin();
    while(f_iter != atomic.fluorescenceYields.end()) {
        QString key = f_iter.key();
        double yield = f_iter.value();
        statement = QString("INSERT INTO fluorescence_yield "
                           "VALUES('%1', "
                           "(SELECT id FROM subshell WHERE symbol='%2'), "
                           "%3)")
               .arg(nuclide)
               .arg(key)
               .arg(yield);
        if(!db->write(statement)) {
            db->write("ROLLBACK");
            return false;
        }
    }
    //end
    db->write("COMMIT");
    return true;
}
