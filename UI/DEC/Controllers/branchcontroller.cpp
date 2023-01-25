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


    }

    return ret;
}
