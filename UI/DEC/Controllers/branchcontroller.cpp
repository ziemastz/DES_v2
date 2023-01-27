#include "branchcontroller.h"
#include "Controllers/nuclidecontroller.h"

BranchController::BranchController() : BaseController()
{

}

QVector<BranchModel> BranchController::getBranches(const QString &nuclide)
{
    QVector<BranchModel> ret;
    statement = QString("SELECT b.idParent, b.transition, b.intensity, b.excited_level_keV, "
                        "b.halfLifeValue, b.halfLifeUncer, u.unit, b.spinParity "
                        "FROM branch b "
                        "LEFT JOIN unit_halflife u ON u.id = b.halfLifeUnit "
                        "WHERE b.idRadionuclide = '%1' "
                        "ORDER BY b.idParent, b.excited_level_keV").arg(nuclide);
    QVector<QVariantList> result = db.read(statement);
    NuclideController nuclideController;

    for(int b=0; b<result.size(); b++) {
        ret << BranchModel();
        int i=0;
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
        statement = QString("SELECT * "
                            "FROM gamma_emission "
                            "WHERE idDaughter = '%1' AND initialLevel_keV = %2")
                .arg(ret.last().daughter.symbol)
                .arg(ret.last().level.excited_level_keV);

        QVector<QVariantList> g_res = db.read(statement);
        for(int g = 0; g< g_res.size(); g++) {
            ret.last().gammes << GammaModel();
            int j=0;
            ret.last().gammes.last().nuclide = g_res.at(g).at(j++).toString();
            ret.last().gammes.last().initialLevel_keV = g_res.at(g).at(j++).toDouble();
            ret.last().gammes.last().finalLevel_keV = g_res.at(g).at(j++).toDouble();
            ret.last().gammes.last().energy = g_res.at(g).at(j++).toDouble();
            ret.last().gammes.last().intensity = g_res.at(g).at(j++).toDouble();
            ret.last().gammes.last().multipolarity = g_res.at(g).at(j++).toString();
            ret.last().gammes.last().total_internal_conversion = g_res.at(g).at(j++).toDouble();
        }

        if(ret.last().transition == "ALPHA") {
            statement = QString("SELECT energy_alpha "
                                "FROM alpha_transition "
                                "WHERE idParent = '%1' AND level_energy_keV = %2")
                    .arg(ret.last().parent.symbol)
                    .arg(ret.last().level.excited_level_keV);

            QVector<QVariantList> a_res = db.read(statement);
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
                                "WHERE b.idParent = '%1' AND b.level_energy_keV = %2")
                    .arg(ret.last().parent.symbol)
                    .arg(ret.last().level.excited_level_keV);
            QVector<QVariantList> b_res = db.read(statement);
            if(b_res.size() == 1) {
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
                                 "WHERE idParent = '%1' AND level_energy_keV = %2")
                     .arg(ret.last().parent.symbol)
                     .arg(ret.last().level.excited_level_keV);
             QVector<QVariantList> e_res = db.read(statement);
             if(e_res.size() == 1) {
                ret.last().ec.intensityEC = e_res.first().at(0).toDouble();
                ret.last().ec.intensityBetaPlus = e_res.first().at(1).toDouble();
             }
             //subsell propability of ec
             statement = QString("SELECT s.symbol, e.intensity "
                                 "FROM ec_probability e "
                                 "LEFT JOIN subshell s on s.id = e.idSubshell "
                                 "WHERE e.idParent = '%1' and e.level_energy_keV = %2")
                     .arg(ret.last().parent.symbol)
                     .arg(ret.last().level.excited_level_keV);
            e_res = db.read(statement);
            for(int i=0; i<e_res.size(); i++) {
                QString key = e_res.at(i).at(0).toString();
                double value = e_res.at(i).at(1).toDouble();
                ret.last().ec.subshell_probability.insert(key,value);
            }
        }

    }

    return ret;
}

bool BranchController::updateBranches(const QString &radionuclide, const QVector<BranchModel> &branches)
{
   //step 1: find in nuclide: parent and daughter
    NuclideController nuclContr;
    QStringList savedNuclides;
    for(int i=0; i<branches.size(); i++) {
       if(!savedNuclides.contains(branches.at(i).parent.symbol)) {
           nuclContr.setNuclide(branches.at(i).parent);
           savedNuclides << branches.at(i).parent.symbol;
       }
       if(!savedNuclides.contains(branches.at(i).daughter.symbol)) {
           nuclContr.setNuclide(branches.at(i).daughter);
           savedNuclides<< branches.at(i).daughter.symbol;
       }
    }
    //step 2: update branches
    for(int i=0; i<branches.size(); i++) {
        db.write(QString("DELETE FROM branch WHERE id"))
    }
    return true;
}

QStringList BranchController::forbiddenness()
{
    QStringList ret;
    statement = QString("SELECT type FROM forbiddenness_type");
    QVector<QVariantList> result = db.read(statement);
    for(int i = 0; i< result.size(); i++) {
        ret << result.at(i).first().toString();
    }
    return ret;
}

QStringList BranchController::expShapeFactors()
{
    QStringList ret;
    statement = QString("SELECT type FROM exp_shape_factor_type");
    QVector<QVariantList> result = db.read(statement);
    for(int i = 0; i< result.size(); i++) {
        ret << result.at(i).first().toString();
    }
    return ret;
}
