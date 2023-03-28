#include "branchcontroller.h"
#include "Controllers/nuclidecontroller.h"
#include <QMap>

BranchController::BranchController() : BaseController()
{

}

QVector<BranchModel> BranchController::getBranches(const QString &nuclide)
{
    QVector<BranchModel> ret;
    statement = QString("SELECT b.id, b.idParent, b.transition, b.intensity, b.excited_level_keV, "
                        "b.halfLifeValue, b.halfLifeUncer, u.unit, b.spinParity, b.idDaughter "
                        "FROM branch b "
                        "LEFT JOIN unit_halflife u ON u.id = b.halfLifeUnit "
                        "WHERE b.idRadionuclide = '%1' "
                        "ORDER BY b.idParent, b.excited_level_keV").arg(nuclide);
    QVector<QVariantList> result = db->read(statement);
    NuclideController nuclideController;

    for(int b=0; b<result.size(); b++) {
        ret << BranchModel();
        int i=0;
        ret.last().id = result.at(b).at(i++).toUInt();
        ret.last().parent = nuclideController.getNuclide(result.at(b).at(i++).toString());
        ret.last().transition = result.at(b).at(i++).toString();
        ret.last().intensity = result.at(b).at(i++).toDouble();
        ret.last().level.excited_level_keV = result.at(b).at(i++).toDouble();
        ret.last().level.halfLifeValue = result.at(b).at(i++).toDouble();
        ret.last().level.halfLifeUncertainty = result.at(b).at(i++).toDouble();
        ret.last().level.halfLifeUnit = result.at(b).at(i++).toString();
        ret.last().level.spinParity = result.at(b).at(i++).toString();
        ret.last().daughter = nuclideController.getNuclide(result.at(b).at(i++).toString());


        //gamma emission of level
        statement = QString("SELECT finalLevel_keV, energy, intensity, multipolarity, total_internal_conversion "
                            "FROM gamma_emission "
                            "WHERE id_branch = %1")
                .arg(ret.last().id);

        QVector<QVariantList> g_res = db->read(statement);
        for(int g = 0; g< g_res.size(); g++) {
            ret.last().gammes << GammaModel();
            ret.last().gammes.last().idBranch = ret.last().id;
            ret.last().gammes.last().nuclide = ret.last().daughter.symbol;
            ret.last().gammes.last().initialLevel_keV = ret.last().level.excited_level_keV;

            int j=0;
            ret.last().gammes.last().finalLevel_keV = g_res.at(g).at(j++).toDouble();
            ret.last().gammes.last().energy = g_res.at(g).at(j++).toDouble();
            ret.last().gammes.last().intensity = g_res.at(g).at(j++).toDouble();
            ret.last().gammes.last().multipolarity = g_res.at(g).at(j++).toString();
            ret.last().gammes.last().total_internal_conversion = g_res.at(g).at(j++).toDouble();

            // gamma conversion electron intensity
            statement = QString("SELECT s.symbol, g.intensity "
                                "FROM gamma_ce g "
                                "LEFT JOIN subshell s ON g.id_subshell = s.id "
                                "WHERE id_branch = %1")
                    .arg(ret.last().id);
            QVector<QVariantList> g_ce_res = db->read(statement);
            for(int c=0;c<g_ce_res.size();c++) {
                ret.last().gammes.last().conversion_electrons.insert(g_ce_res.at(c).first().toString(),
                                                                     g_ce_res.at(c).last().toDouble());
            }
        }

        if(ret.last().transition == "ALPHA") {
            statement = QString("SELECT energy_alpha "
                                "FROM alpha_transition "
                                "WHERE id_branch = %1")
                    .arg(ret.last().id);

            QVector<QVariantList> a_res = db->read(statement);
            if(a_res.size() == 1) {
                ret.last().alpha_energy_kev = a_res.first().first().toDouble();
            }
        }
        if(ret.last().transition == "BETA-") {
            statement = QString("SELECT b.endpoint_energy_keV, "
                                "f.type, b.coeff_a, b.coeff_b, b.coeff_c, b.coeff_d, b.coeff_e, "
                                "e.type, b.exp_coeff_a, b.exp_coeff_b, b.exp_coeff_c, b.exp_coeff_d, "
                                "b.mixing_ratio "
                                "FROM beta_transition b "
                                "LEFT JOIN forbiddenness_type f on b.forbiddenness = f.id "
                                "LEFT JOIN exp_shape_factor_type e on b.exp_shape_factor = e.id "
                                "WHERE b.id_branch = %1")
                    .arg(ret.last().id);

            QVector<QVariantList> b_res = db->read(statement);
            if(b_res.size() == 1) {
                ret.last().beta.idBranch = ret.last().id;
                int i=0;
                ret.last().beta.endpoint_energy_keV = b_res.first().at(i++).toDouble();
                ret.last().beta.forbiddenness = b_res.first().at(i++).toString();
                ret.last().beta.coeff_a = b_res.first().at(i++).toDouble();
                ret.last().beta.coeff_b = b_res.first().at(i++).toDouble();
                ret.last().beta.coeff_c = b_res.first().at(i++).toDouble();
                ret.last().beta.coeff_d = b_res.first().at(i++).toDouble();
                ret.last().beta.coeff_e = b_res.first().at(i++).toDouble();
                ret.last().beta.exp_shape_factor = b_res.first().at(i++).toString();
                ret.last().beta.exp_coeff_a = b_res.first().at(i++).toDouble();
                ret.last().beta.exp_coeff_b = b_res.first().at(i++).toDouble();
                ret.last().beta.exp_coeff_c = b_res.first().at(i++).toDouble();
                ret.last().beta.exp_coeff_d = b_res.first().at(i++).toDouble();
                ret.last().beta.mixing_ratio = b_res.first().at(i++).toDouble();
            }
        }
        if(ret.last().transition == "EC") {
             statement = QString("SELECT intensity_ec, intensity_beta_plus "
                                 "FROM ec_transition "
                                 "WHERE id_branch = %1")
                     .arg(ret.last().id);

             QVector<QVariantList> e_res = db->read(statement);
             if(e_res.size() == 1) {
                ret.last().ec.intensityEC = e_res.first().at(0).toDouble();
                ret.last().ec.intensityBetaPlus = e_res.first().at(1).toDouble();
             }
             //subsell propability of ec
             statement = QString("SELECT s.symbol, e.intensity "
                                 "FROM ec_probability e "
                                 "LEFT JOIN subshell s on s.id = e.id_subshell "
                                 "WHERE e.id_branch = %1")
                     .arg(ret.last().id);

             e_res = db->read(statement);
            for(int i=0; i<e_res.size(); i++) {
                QString key = e_res.at(i).at(0).toString();
                double value = e_res.at(i).at(1).toDouble();
                ret.last().ec.subshell_probability.insert(key,value);
            }
            statement = QString("SELECT b.endpoint_energy_keV, "
                                "f.type, b.coeff_a, b.coeff_b, b.coeff_c, b.coeff_d, b.coeff_e, "
                                "e.type, b.exp_coeff_a, b.exp_coeff_b, b.exp_coeff_c, b.exp_coeff_d, "
                                "b.mixing_ratio "
                                "FROM betaPlus_transition b "
                                "LEFT JOIN forbiddenness_type f on b.forbiddenness = f.id "
                                "LEFT JOIN exp_shape_factor_type e on b.exp_shape_factor = e.id "
                                "WHERE b.id_branch = %1")
                    .arg(ret.last().id);

            QVector<QVariantList> b_res = db->read(statement);
            if(b_res.size() == 1) {
                ret.last().ec.betaPlus.idBranch = ret.last().id;
                int i=0;
                ret.last().ec.betaPlus.endpoint_energy_keV = b_res.first().at(i++).toDouble();
                ret.last().ec.betaPlus.forbiddenness = b_res.first().at(i++).toString();
                ret.last().ec.betaPlus.coeff_a = b_res.first().at(i++).toDouble();
                ret.last().ec.betaPlus.coeff_b = b_res.first().at(i++).toDouble();
                ret.last().ec.betaPlus.coeff_c = b_res.first().at(i++).toDouble();
                ret.last().ec.betaPlus.coeff_d = b_res.first().at(i++).toDouble();
                ret.last().ec.betaPlus.coeff_e = b_res.first().at(i++).toDouble();
                ret.last().ec.betaPlus.exp_shape_factor = b_res.first().at(i++).toString();
                ret.last().ec.betaPlus.exp_coeff_a = b_res.first().at(i++).toDouble();
                ret.last().ec.betaPlus.exp_coeff_b = b_res.first().at(i++).toDouble();
                ret.last().ec.betaPlus.exp_coeff_c = b_res.first().at(i++).toDouble();
                ret.last().ec.betaPlus.exp_coeff_d = b_res.first().at(i++).toDouble();
                ret.last().ec.betaPlus.mixing_ratio = b_res.first().at(i++).toDouble();
            }
        }

    }

    return ret;
}

bool BranchController::updateBranches(const QString &radionuclide, const QVector<BranchModel> &branches)
{
    if(!db->write("BEGIN TRANSACTION"))
        return false;
   //step 1: find in nuclide: parent and daughter
    NuclideController nuclContr;
    QStringList savedNuclides;
    for(int i=0; i<branches.size(); i++) {
       if(!savedNuclides.contains(branches.at(i).parent.symbol)) {
           if(!nuclContr.setNuclide(branches.at(i).parent)) {
               db->write("ROLLBACK");
               return false;
           }
           savedNuclides << branches.at(i).parent.symbol;
       }
       if(!savedNuclides.contains(branches.at(i).daughter.symbol)) {
           if(!nuclContr.setNuclide(branches.at(i).daughter)) {
               db->write("ROLLBACK");
               return false;
           }
           savedNuclides<< branches.at(i).daughter.symbol;
       }
    }
    //step 2: delete old branches
    if(!db->write(QString("DELETE FROM branch WHERE idRadionuclide='%1'").arg(radionuclide))) {
        db->write("ROLLBACK");
        return false;
    }
    //step 3: insert branches
    for(int i=0; i<branches.size(); i++) {
        // insert branch
        statement = QString("INSERT INTO branch(idRadionuclide, idParent, transition, intensity, excited_level_keV, halfLifeValue, halfLifeUncer, halfLifeUnit, spinParity, idDaughter) "
                            "VALUES('%1', '%2', '%3', %4, %5, %6, %7, (SELECT id FROM unit_halflife WHERE unit='%8'), '%9', '%10')")
                .arg(radionuclide)
                .arg(branches.at(i).parent.symbol)
                .arg(branches.at(i).transition)
                .arg(branches.at(i).intensity)
                .arg(branches.at(i).level.excited_level_keV)
                .arg(branches.at(i).level.halfLifeValue)
                .arg(branches.at(i).level.halfLifeUncertainty)
                .arg(branches.at(i).level.halfLifeUnit)
                .arg(branches.at(i).level.spinParity)
                .arg(branches.at(i).daughter.symbol);
        if(!db->write(statement)) {
            db->write("ROLLBACK");
            return false;
        }
        uint id_branch = db->getLastInsertId();

        //gamma emisions
        for(int g=0;g<branches.at(i).gammes.size();g++) {
            statement = QString("INSERT INTO gamma_emission(id_branch, finalLevel_keV, energy, intensity, multipolarity, total_internal_conversion) "
                                "VALUES(%1, %2, %3, %4, '%5', %6)")
                    .arg(id_branch)
                    .arg(branches.at(i).gammes.at(g).finalLevel_keV)
                    .arg(branches.at(i).gammes.at(g).energy)
                    .arg(branches.at(i).gammes.at(g).intensity)
                    .arg(branches.at(i).gammes.at(g).multipolarity)
                    .arg(branches.at(i).gammes.at(g).total_internal_conversion);
            if(!db->write(statement)) {
                db->write("ROLLBACK");
                return false;
            }
            // conversion electron emisions
            //QMapIterator<QString,double> iter(branches.at(i).gammes.at(g).conversion_electrons);
            QMap<QString,double>::const_iterator iter = branches.at(i).gammes.at(g).conversion_electrons.begin();
            while(iter != branches.at(i).gammes.at(g).conversion_electrons.end()) {
                QString key = iter.key();
                double value = iter.value();
                statement = QString("INSERT INTO gamma_ce(id_branch, id_subshell, intensity) "
                                    "VALUES (%1, (SELECT id FROM subshell WHERE symbol ='%2'), %3)")
                        .arg(id_branch)
                        .arg(key)
                        .arg(value);
                if(!db->write(statement)) {
                    db->write("ROLLBACK");
                    return false;
                }
                ++iter;
            }
        }

        // alpha transition
        if(branches.at(i).transition == "ALPHA") {
            statement = QString("INSERT INTO alpha_transition(id_branch,energy_alpha)"
                                "VALUES(%1, %2)")
                    .arg(id_branch)
                    .arg(branches.at(i).alpha_energy_kev);
            if(!db->write(statement)) {
                db->write("ROLLBACK");
                return false;
            }
        }

        // beta- transition
        if(branches.at(i).transition == "BETA-") {
            statement = QString("INSERT INTO beta_transition "
                                "VALUES(%1, %2, "
                                "(SELECT id FROM forbiddenness_type WHERE type='%3'), "
                                "%4, %5, %6, %7, %8,"
                                "(SELECT id FROM exp_shape_factor_type WHERE type='%9'), "
                                "%10, %11, %12, %13, %14)")
                    .arg(id_branch)
                    .arg(branches.at(i).beta.endpoint_energy_keV)
                    .arg(branches.at(i).beta.forbiddenness)
                    .arg(branches.at(i).beta.coeff_a)
                    .arg(branches.at(i).beta.coeff_b)
                    .arg(branches.at(i).beta.coeff_c)
                    .arg(branches.at(i).beta.coeff_d)
                    .arg(branches.at(i).beta.coeff_e)
                    .arg(branches.at(i).beta.exp_shape_factor)
                    .arg(branches.at(i).beta.exp_coeff_a)
                    .arg(branches.at(i).beta.exp_coeff_b)
                    .arg(branches.at(i).beta.exp_coeff_c)
                    .arg(branches.at(i).beta.exp_coeff_d)
                    .arg(branches.at(i).beta.mixing_ratio);
            if(!db->write(statement)) {
                db->write("ROLLBACK");
                return false;
            }
        }

        //EC transition
        if(branches.at(i).transition == "EC") {
            statement = QString("INSERT INTO ec_transition(id_branch, intensity_ec, intensity_beta_plus) "
                                "VALUES(%1, %2, %3)")
                    .arg(id_branch)
                    .arg(branches.at(i).ec.intensityEC)
                    .arg(branches.at(i).ec.intensityBetaPlus);
            if(!db->write(statement)) {
                db->write("ROLLBACK");
                return false;
            }
            QMap<QString,double>::const_iterator iter = branches.at(i).ec.subshell_probability.begin();
            while(iter != branches.at(i).ec.subshell_probability.end()) {
                QString key = iter.key();
                double value = iter.value();
                statement = QString("INSERT INTO ec_probability(id_branch, id_subshell, intensity) "
                                    "VALUES (%1, (SELECT id FROM subshell WHERE symbol ='%2'), %3)")
                        .arg(id_branch)
                        .arg(key)
                        .arg(value);
                if(!db->write(statement)) {
                    db->write("ROLLBACK");
                    return false;
                }
                ++iter;
            }
            statement = QString("INSERT INTO betaPlus_transition "
                                "VALUES(%1, %2, "
                                "(SELECT id FROM forbiddenness_type WHERE type='%3'), "
                                "%4, %5, %6, %7, %8,"
                                "(SELECT id FROM exp_shape_factor_type WHERE type='%9'), "
                                "%10, %11, %12, %13, %14)")
                    .arg(id_branch)
                    .arg(branches.at(i).ec.betaPlus.endpoint_energy_keV)
                    .arg(branches.at(i).ec.betaPlus.forbiddenness)
                    .arg(branches.at(i).ec.betaPlus.coeff_a)
                    .arg(branches.at(i).ec.betaPlus.coeff_b)
                    .arg(branches.at(i).ec.betaPlus.coeff_c)
                    .arg(branches.at(i).ec.betaPlus.coeff_d)
                    .arg(branches.at(i).ec.betaPlus.coeff_e)
                    .arg(branches.at(i).ec.betaPlus.exp_shape_factor)
                    .arg(branches.at(i).ec.betaPlus.exp_coeff_a)
                    .arg(branches.at(i).ec.betaPlus.exp_coeff_b)
                    .arg(branches.at(i).ec.betaPlus.exp_coeff_c)
                    .arg(branches.at(i).ec.betaPlus.exp_coeff_d)
                    .arg(branches.at(i).ec.betaPlus.mixing_ratio);
            if(!db->write(statement)) {
                db->write("ROLLBACK");
                return false;
            }
        }
    }
    db->write("COMMIT");
    return true;
}

QStringList BranchController::forbiddenness()
{
    QStringList ret;
    statement = QString("SELECT type FROM forbiddenness_type");
    QVector<QVariantList> result = db->read(statement);
    for(int i = 0; i< result.size(); i++) {
        ret << result.at(i).first().toString();
    }
    return ret;
}

QStringList BranchController::expShapeFactors()
{
    QStringList ret;
    statement = QString("SELECT type FROM exp_shape_factor_type");
    QVector<QVariantList> result = db->read(statement);
    for(int i = 0; i< result.size(); i++) {
        ret << result.at(i).first().toString();
    }
    return ret;
}
